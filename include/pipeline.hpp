#pragma once

#include <vulkan/vulkan.h>

namespace vk_boost::pipeline {

VkPipelineRasterizationStateCreateInfo defaultRasterizerInfo();
VkPipelineColorBlendStateCreateInfo defaultColorBlendStateInfo();
VkPipelineMultisampleStateCreateInfo defaultMultisampleStateInfo();
VkPipelineInputAssemblyStateCreateInfo defaultInputAssemblyStateInfo();

} // namespace vk_boost
