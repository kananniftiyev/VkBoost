//
// Created by kanan on 6/7/2025.
//

#include "vkxtra/commands.h"

#include <cassert>

[[nodiscard]]
VkCommandPool vkxtra::commands::createCommandPool(const VkDevice& device, std::uint32_t queue_family_index) {
    VkCommandPoolCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    info.queueFamilyIndex = queue_family_index;

    VkCommandPool pool;
    const auto res = vkCreateCommandPool(device, &info, nullptr, &pool );

    assert(res == VK_SUCCESS);
    return pool;
}

[[nodiscard]]
VkCommandBuffer vkxtra::commands::allocatePrimaryCommandBuffer(const VkDevice &device, const VkCommandPool &pool) {
    VkCommandBufferAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.pNext = nullptr;
    info.commandPool = pool;
    info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    info.commandBufferCount = 1;

    VkCommandBuffer cmd;
    const auto res = vkAllocateCommandBuffers(device, &info, &cmd);
    assert(res == VK_SUCCESS);

    return cmd;

}
