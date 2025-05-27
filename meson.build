project('vk-boost', 'cpp', version: '0.1.0')

debug_args = []

if get_option('buildtype') == 'debug'
    debug_args += ['-DDEBUG']
endif

cxx_std = 'c++20'

vulkan_dep = dependency('vulkan', required: true)

shaderc_dep = dependency('shaderc', required: true)

spdlog_dep = dependency('spdlog', required: true)

xxhash_dep = dependency('libxxhash', required: true)

mini_dep = declare_dependency(include_directories: include_directories('./third_party/mINI/src'))

src_files = files(
    'src/main.cpp',
    'src/pipeline.cpp',
    'src/shader_compiler.cpp',
    'src/sync.cpp',
    'src/vk_shader.cpp',
)

deps = [vulkan_dep, shaderc_dep, spdlog_dep, mini_dep, xxhash_dep]

vk_boost_lib = static_library(
    'vk-boost-lib',
    src_files,
    dependencies: deps,
    include_directories: include_directories('include'),
    cpp_args: debug_args,
)

vk_boost_test = executable(
    'vk-boost-tests',
    include_directories: include_directories('include'),
    sources: src_files,
    dependencies: deps,
    link_with: vk_boost_lib,
    cpp_args: debug_args,
)