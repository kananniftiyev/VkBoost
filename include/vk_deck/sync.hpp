#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <cassert>

namespace vk_deck::sync
{
    VkFence createFence(const VkDevice &device);
    VkSemaphore createSemaphore(const VkDevice &device);
}
