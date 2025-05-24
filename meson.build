project('vk-boost', 'cpp', version: '0.1.0')

cxx_std = 'c++20'

vulkan_dep = dependency('vulkan', required: true)

src_files = files(
  'src/pipeline.cpp'
)

vk_boost_lib = static_library('vk-boost-lib', 
src_files, dependencies: [vulkan_dep], include_directories: include_directories('include'))