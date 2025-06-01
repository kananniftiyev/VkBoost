#pragma once

#include <vulkan/vulkan.h>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_vulkan.h"
#include <stdexcept>

namespace vk_deck::imgui{
	void initImgui(const VkDevice& device, const VkInstance& instance, const VkPhysicalDevice& physical_device, 
		const VkQueue& queue, const VkFormat& format, SDL_Window& window);
	void shutdownImgui(const VkDevice& device, VkDescriptorPool& pool);
}