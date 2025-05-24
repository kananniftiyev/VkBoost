#include "sync.hpp"

[[nodiscard]]
VkFence vk_boost::sync::createFence(const VkDevice& device){
    VkFence fence;

    VkFenceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    assert(vkCreateFence(device, &info, nullptr, &fence) == VK_SUCCESS);

    return fence;
}

[[nodiscard]]
VkSemaphore vk_boost::sync::createSemaphore(const VkDevice& device){
    VkSemaphore semaphore;

    VkSemaphoreCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    info.pNext = nullptr;

    assert(vkCreateSemaphore(device, &info, nullptr, &semaphore));

    return semaphore;
}
