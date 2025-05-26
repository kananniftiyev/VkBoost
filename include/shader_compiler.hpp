#pragma once

#include <chrono>
#include <filesystem>
#include <fstream>
#include <memory>
#include <mini/ini.h>
#include <shaderc/shaderc.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace fs = std::filesystem;

namespace vk_boost::shader
{

class shader_compiler
{
private:
    std::string _folder_path;
    fs::path _compiled_shader_folder;
    shaderc::Compiler _compiler;
    std::vector<std::string> _vert_files;
    std::vector<std::string> _frag_files;

    static bool changeToProjectPath(const std::vector<fs::path> &markers = {".git", "CMakeLists.txt", "Makefile"});

    fs::path compileShader(fs::path path);

    bool isShaderModified(fs::path path, mINI::INIStructure &ini);

    std::string fileLastWriteTimeStr(const fs::path &path);


public:
    shader_compiler(std::string file_path);
    ~shader_compiler();
};

} // namespace vk_boost::shader
