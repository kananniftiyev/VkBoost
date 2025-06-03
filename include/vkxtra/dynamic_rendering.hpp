#pragma once

#include <vulkan/vulkan.h>

namespace vkxtra::dynamic_rendering {
	void changeImageLayout(VkCommandBuffer cmd, VkImage image, VkImageLayout old_layout, VkImageLayout new_layout);

	VkRenderingAttachmentInfoKHR defaultColorAttachmentKHR(VkImageView image_view, VkClearValue clear_value);
	VkRenderingAttachmentInfoKHR defaultDepthAttachmentKHR(VkImageView image_view, VkClearValue depth_value);
}