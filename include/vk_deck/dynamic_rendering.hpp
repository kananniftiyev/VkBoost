#pragma once

#include <vulkan/vulkan.h>

namespace vk_deck::dynamic_rendering {
	void changeImageLayout(VkCommandBuffer cmd, VkImage image, VkImageLayout old_layout, VkImageLayout new_layout);
}