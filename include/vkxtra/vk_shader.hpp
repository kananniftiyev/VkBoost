#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <fstream>
#include <vector>

namespace vkxtra::shader
{
  /// @brief Creates VkShaderModule from given path.
  /// @param device VkDevice Instance.
  /// @param spv_path SPRI-V shader path.
  /// @return VkShaderModule.
  VkShaderModule createShaderModule(const VkDevice &device, const std::string &spv_path);
} // namespace vk_boost::shader
