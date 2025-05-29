#pragma once

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
#include <vector>
#include <stdexcept>

namespace vk_boost::buffer
{
  struct buffer_resource
  {
    VkBuffer buffer;
    VmaAllocation allocation;
  };

  enum class BufferAlloctionType
  {
    CPU_ONLY_BUFFER,
    GPU_ONLY_BUFFER,
    CPU_TO_GPU_BUFFER
  };

  template <typename T>
  buffer_resource createBuffer(const VmaAllocator &allocator, const std::vector<T> &input_data, BufferAlloctionType usage_type, VkBufferUsageFlags usage_flag)
  {
    const size_t allocation_size = input_data.size() * sizeof(T);

    VkBufferCreateInfo buffer_create_info{};
    buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_create_info.pNext = nullptr;
    buffer_create_info.size = allocation_size;
    buffer_create_info.usage = usageFlagBit;
    buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    const VmaMemoryUsage memory_usage = [&]()
    {
      switch (BufferAlloctionType)
      {
      case BufferAlloctionType::CPU_ONLY_BUFFER:
        return VMA_MEMORY_USAGE_CPU_ONLY;
      case BufferAlloctionType::CPU_TO_GPU_BUFFER:
        return VMA_MEMORY_USAGE_CPU_TO_GPU;
      case BufferAlloctionType::GPU_ONLY_BUFFER:
        return VMA_MEMORY_USAGE_GPU_ONLY;
      default:
        return VMA_MEMORY_USAGE_UNKNOWN;
      }
    }();

    VmaAllocationCreateInfo allocation_create_info{};
    allocation_create_info.usage = memory_usage;

    buffer_resource out_buffer;
    auto res = vmaCreateBuffer(allocator, &buffer_create_info, &allocation_create_info, &out_buffer.buffer, &out_buffer.allocation, nullptr);

    if (res != VK_SUCCESS)
    {
      throw std::runtime_error("could not create buffer.");
    }

    void *pData = nullptr;
    vmaMapMemory(allocator, out_buffer.allocation, &pData);
    std::memcpy(pData, input_data.data(), allocation_size);
    vmaUnmapMemory(allocator, out_buffer.allocation);

    return out_buffer;
  }

} // namespace vk_boost::buffer
