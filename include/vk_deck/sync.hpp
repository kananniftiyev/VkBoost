#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <cassert>

namespace vk_deck::sync
{
    /// @brief Creates simple VkFence.
    /// @param device VkDevice instance.
    /// @return VkFencce
    VkFence createFence(const VkDevice &device);

    /// @brief Creates simple VkSempahore.
    /// @param device VkDevice instance.
    /// @return VkSemaphore.
    VkSemaphore createSemaphore(const VkDevice &device);
}
