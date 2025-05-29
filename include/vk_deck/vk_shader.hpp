#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <fstream>
#include <vector>

namespace vk_deck::shader
{
  VkShaderModule createShaderModule(const VkDevice &device, const std::string &spv_path);
} // namespace vk_boost::shader
