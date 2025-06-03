#pragma once

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
#include <vector>
#include <stdexcept>

namespace vkxtra::buffer
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

  /// @brief This function creates buffer but does not map the data into it.
  /// @tparam T Type of data
  /// @param allocator VmaAllocator instance.
  /// @param input_data Input data such as vertecies or indices.
  /// @param usage_type How buffer will be used (CPU, GPU).
  /// @param usage_flag What kind of buffer it is gonna be (Uniform, Transfer_src, Vertex).
  /// @return Buffer resource (VkBuffer and VMAllocation).
  template <typename T>
  buffer_resource createBuffer(const VmaAllocator &allocator, const std::vector<T> &input_data, BufferAlloctionType usage_type, VkBufferUsageFlags usage_flag)
  {
    const size_t allocation_size = input_data.size() * sizeof(T);

    VkBufferCreateInfo buffer_create_info{};
    buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_create_info.pNext = nullptr;
    buffer_create_info.size = allocation_size;
    buffer_create_info.usage = usage_flag;
    buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    const VmaMemoryUsage memory_usage = [&]()
    {
      switch (usage_type)
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

    return out_buffer;
  }

  /// @brief  This function creates and maps data into that buffer.
  /// @tparam T Type of data.
  /// @param allocator VmaAllocator instance.
  /// @param input_data Input data such as vertecies or indices.
  /// @param usage_type How buffer will be used (CPU, GPU).
  /// @param usage_flag What kind of buffer it is gonna be (Uniform, Transfer_src, Vertex).
  /// @return Buffer resource (VkBuffer and VmaAllocation).
  template <typename T>
  buffer_resource createBufferAndData(const VmaAllocator &allocator, const std::vector<T> &input_data, BufferAlloctionType usage_type, VkBufferUsageFlags usage_flag)
  {
    auto buffer_in = createBuffer(allocator, input_data, usage_type, usage_flag);

    void *pData = nullptr;
    vmaMapMemory(allocator, buffer_in.allocation, &pData);
    memcpy(pData, input_data.data(), input_data.size() * sizeof(T));
    vmaUnmapMemory(allocator, buffer_in.allocation);

    return buffer_in;
  }

} // namespace vk_boost::buffer
