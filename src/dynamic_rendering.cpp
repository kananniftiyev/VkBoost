#include "vk_deck/dynamic_rendering.hpp"

void vk_deck::dynamic_rendering::changeImageLayout(VkCommandBuffer cmd, VkImage image, VkImageLayout old_layout, VkImageLayout new_layout)
{
	VkImageMemoryBarrier2 barrier_info{};
	barrier_info.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
	barrier_info.pNext = nullptr;

	barrier_info.srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
	barrier_info.srcAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT;
	barrier_info.dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
	barrier_info.dstAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT | VK_ACCESS_2_MEMORY_READ_BIT;

	barrier_info.oldLayout = old_layout;
	barrier_info.newLayout = new_layout;
	barrier_info.image = image;

	VkImageAspectFlags aspect_flags = (new_layout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;

	VkImageSubresourceRange subresource_range{};
	subresource_range.aspectMask = aspect_flags;
	subresource_range.baseMipLevel = 0;
	subresource_range.levelCount = VK_REMAINING_MIP_LEVELS;
	subresource_range.baseArrayLayer = 0;
	subresource_range.layerCount = VK_REMAINING_ARRAY_LAYERS;

	barrier_info.subresourceRange = subresource_range;

	VkDependencyInfo dependency_info{};
	dependency_info.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
	dependency_info.imageMemoryBarrierCount = 1;
	dependency_info.pImageMemoryBarriers = &barrier_info;

	vkCmdPipelineBarrier2(cmd, &dependency_info);	
}
