#include "vk_shader.hpp"

[[nodiscard]]
VkShaderModule vk_boost::shader::createShaderModule(const VkDevice &device, const std::string &spv_path)
{

  std::ifstream input_shader(spv_path, std::ios::ate | std::ios::binary);

  if (!input_shader)
  {
    return VK_NULL_HANDLE;
  }

  size_t size = static_cast<uint32_t>(input_shader.tellg());
  if (size % sizeof(uint32_t) != 0)
  {
    return VK_NULL_HANDLE;
  }

  std::vector<uint32_t> spv_code(size / sizeof(uint32_t));
  input_shader.seekg(0);
  input_shader.read(reinterpret_cast<char *>(spv_code.data()), size);

  VkShaderModuleCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  info.pNext = nullptr;
  info.codeSize = size;
  info.pCode = spv_code.data();

  VkShaderModule shader_module;
  vkCreateShaderModule(device, &info, nullptr, &shader_module);

  return shader_module;
}