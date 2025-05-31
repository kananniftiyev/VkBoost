cmake_minimum_required(VERSION 3.16)
project(vk_deck VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file" FORCE)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set DEBUG define if in debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

# Enable testing
include(CTest)

# Use vcpkg toolchain if provided
if(DEFINED ENV{VCPKG_ROOT})
    message(STATUS "Using vcpkg from $ENV{VCPKG_ROOT}")
endif()

# Dependencies (assume vcpkg will handle these)
find_package(Vulkan REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(unofficial-shaderc CONFIG REQUIRED)
find_package(Catch2 REQUIRED)

# Manual includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/mINI/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/vma/include)

# Source files
set(SRC_FILES
    src/buffer.cpp
    src/pipeline.cpp
    src/shader_compiler.cpp
    src/sync.cpp
    src/vk_shader.cpp
    src/dynamic_rendering.cpp
)

set(TEST_FILES
    tests/main.cpp
    tests/pipeline_test.cpp
)

# Static library
add_library(vk_deck_lib STATIC ${SRC_FILES})
target_link_libraries(vk_deck_lib PRIVATE
    Vulkan::Vulkan
    unofficial-shaderc
    spdlog::spdlog
)

# Test executable
add_executable(vk_deck_test ${TEST_FILES})
target_link_libraries(vk_deck_test PRIVATE
    vk_deck_lib
    Catch2::Catch2WithMain
)

# Add test
add_test(NAME VkDeckTest COMMAND vk_deck_test)
