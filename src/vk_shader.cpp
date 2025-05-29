#include "vk_boost/vk_shader.hpp"

[[nodiscard]]
VkShaderModule vk_boost::shader::createShaderModule(const VkDevice &device, const std::string &spv_path)
{

  std::ifstream input_shader(spv_path, std::ios::ate | std::ios::binary);

  if (!input_shader.is_open())
  {
    return VK_NULL_HANDLE;
  }

  std::streamsize file_size = input_shader.tellg();
  if (file_size <= 0 || file_size % sizeof(uint32_t) != 0)
  {
    return VK_NULL_HANDLE;
  }

  size_t size = static_cast<size_t>(file_size);
  std::vector<uint32_t> spv_code(size / sizeof(uint32_t));

  input_shader.seekg(0);
  input_shader.read(reinterpret_cast<char *>(spv_code.data()), size);

  VkShaderModuleCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  info.pNext = nullptr;
  info.codeSize = size;
  info.pCode = spv_code.data();

  VkShaderModule shader_module;
  auto res = vkCreateShaderModule(device, &info, nullptr, &shader_module);

  if (res != VK_SUCCESS)
  {
    return VK_NULL_HANDLE;
  }

  return shader_module;
}