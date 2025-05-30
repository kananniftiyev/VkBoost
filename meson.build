project('vk_deck', 'cpp', version: '0.1.0')

debug_args = []

if get_option('buildtype') == 'debug'
    debug_args += ['-DDEBUG']
endif

cxx_std = 'c++17'

vulkan_dep = dependency('vulkan', required: true)

shaderc_dep = dependency('shaderc', required: true)

catch2_dep = dependency('catch2', required: true)

spdlog_dep = dependency('spdlog', required: true)

mini_dep = declare_dependency(include_directories: include_directories('./third_party/mINI/src'))

vma_dep = declare_dependency(
    include_directories: include_directories('./third_party/vma/include'),
)

src_files = files(
    'src/buffer.cpp',
    'src/pipeline.cpp',
    'src/shader_compiler.cpp',
    'src/sync.cpp',
    'src/vk_shader.cpp',
)

test_files = files('tests/main.cpp', 'tests/pipeline_test.cpp')

deps = [vulkan_dep, shaderc_dep, spdlog_dep, mini_dep, vma_dep, catch2_dep]

vk_deck_lib = static_library(
    'vk_deck_lib',
    src_files,
    dependencies: deps,
    include_directories: include_directories('include'),
    cpp_args: debug_args,
)

vk_deck_test = executable(
    'vk_deck_test',
    include_directories: include_directories('include'),
    sources: test_files,
    dependencies: deps,
    link_with: vk_deck_lib,
    cpp_args: debug_args,
)

test('VkDeck Test', vk_deck_test)