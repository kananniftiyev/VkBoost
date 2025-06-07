cmake_minimum_required(VERSION 3.16)
project(vkxtra VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file" FORCE)
set(CMAKE_PREFIX_PATH "$ENV{VCPKG_ROOT}/installed/x64-windows")

# C++ standard
set(CMAKE_CXX_STANDARD 20)
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
find_package(imgui CONFIG REQUIRED)

# Manual includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/mINI/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/vma ${CMAKE_BINARY_DIR}/vma)


# Source files
set(SRC_FILES
    src/buffer.cpp
    src/pipeline.cpp
    src/shader_compiler.cpp
    src/sync.cpp
    src/vk_shader.cpp
    src/dynamic_rendering.cpp
    src/imgui.cpp
)

set(TEST_FILES
    tests/main.cpp
    tests/pipeline_test.cpp
)

# Static library
add_library(vkxtra STATIC ${SRC_FILES})
target_link_libraries(vkxtra PRIVATE
    Vulkan::Vulkan
    unofficial::shaderc::shaderc
    spdlog::spdlog
    imgui::imgui
        GPUOpen::VulkanMemoryAllocator
)

target_include_directories(vkxtra PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Test executable
add_executable(vkxtra_test ${TEST_FILES})
target_link_libraries(vkxtra_test PRIVATE
        vkxtra
    Catch2::Catch2WithMain
)



# Add test
add_test(NAME VKXTRA COMMAND vkxtra)
