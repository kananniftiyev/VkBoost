#pragma once

#include <vulkan/vulkan.h>

namespace vk_deck::pipeline
{

  VkPipelineRasterizationStateCreateInfo defaultRasterizerStateInfo();
  VkPipelineColorBlendStateCreateInfo defaultColorBlendStateInfo();
  VkPipelineMultisampleStateCreateInfo defaultMultisampleStateInfo();
  VkPipelineInputAssemblyStateCreateInfo defaultInputAssemblyStateInfo();
  VkPipelineDepthStencilStateCreateInfo defaultDepthStencilStateInfo();

} // namespace vk_boost
