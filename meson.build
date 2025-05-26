project('vk-boost', 'cpp', version: '0.1.0')

cxx_std = 'c++20'

vulkan_dep = dependency('vulkan', required: true)

shaderc_dep = dependency('shaderc', required: true)

spdlog_dep = dependency('spdlog', required: true)

xxhash_dep = dependency('libxxhash', required: true)

# xxhash_dep = dependency('xxhash', required: true)

mINI_dep = declare_dependency(include_directories: include_directories('./third_party/mINI/src'))

src_files = files(
    'src/pipeline.cpp',
    'src/shader_compiler.cpp',
    'src/sync.cpp',
)

deps = [vulkan_dep, shaderc_dep, spdlog_dep, mINI_dep, xxhash_dep]

vk_boost_lib = static_library(
    'vk-boost-lib',
    src_files,
    dependencies: deps,
    include_directories: include_directories('include'),
)

# vk_boost_test = executable(
#     'vk-boost-tests',
#     include_directories: include_directories('include'),
#     sources: src_files,
#     dependencies: deps,
#     link_with: vk_boost_lib,
# )