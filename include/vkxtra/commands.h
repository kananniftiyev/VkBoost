//
// Created by kanan on 6/7/2025.
//

#ifndef COMMANDS_H
#define COMMANDS_H
#include <cstdint>
#include <vulkan/vulkan_core.h>

namespace vkxtra::commands {
    VkCommandPool createCommandPool(const VkDevice& device, std::uint32_t queue_family_index);
    VkCommandBuffer allocatePrimaryCommandBuffer(const VkDevice& device, const VkCommandPool& pool);
}

#endif //COMMANDS_H
