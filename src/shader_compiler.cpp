#include "vk_deck/shader_compiler.hpp"

namespace
{
#ifdef DEBUG
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#else
#define LOG_INFO(...) \
    do                \
    {                 \
    } while (0)
#define LOG_WARN(...) \
    do                \
    {                 \
    } while (0)
#define LOG_ERROR(...) \
    do                 \
    {                  \
    } while (0)
#endif

} // namespace

bool vk_deck::shader::shader_compiler::changeToProjectPath(const std::vector<fs::path> &markers)
{
    while (true)
    {
        for (const auto &marker : markers)
        {
            if (fs::exists(marker))
            {
                return true;
            }
        }

        if (fs::current_path().has_parent_path())
        {
            fs::current_path(fs::current_path().parent_path());
        }
        else
        {
            break;
        }
    }

    return false;
}

fs::path vk_deck::shader::shader_compiler::compileShader(fs::path path)
{
    shaderc::CompileOptions options;
    options.SetOptimizationLevel(shaderc_optimization_level_size);

    std::ifstream input(path);
    if (!input)
    {
        LOG_ERROR("Could not open input file for read");
        return "";
    }

    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string source{buffer.str()};

    shaderc_shader_kind kind = (path.extension() == ".vert")
                                   ? shaderc_shader_kind::shaderc_glsl_default_vertex_shader
                                   : shaderc_shader_kind::shaderc_glsl_default_fragment_shader;
    auto module = this->_compiler.CompileGlslToSpv(source, kind, path.string().c_str(), options);

    if (module.GetCompilationStatus() != shaderc_compilation_status_success)
    {
        LOG_ERROR("Could not compile shader : {}", path.string());
        return "";
    }

    std::vector<uint32_t> spriv{module.cbegin(), module.cend()};

    std::string kind_str = (path.extension() == ".vert") ? "-vert" : "-frag";

    fs::path out_path = this->_compiled_shader_folder / (path.stem().string() + kind_str + ".spv");

    LOG_INFO("{}", out_path.string());
    std::ofstream out(out_path, std::ios::binary);
    if (!out)
    {
        LOG_ERROR("Failed to open file for writing");
        return "";
    }

    out.write(reinterpret_cast<const char *>(spriv.data()), spriv.size() * sizeof(uint32_t));
    out.close();

    return out_path;
}

bool vk_deck::shader::shader_compiler::isShaderModified(fs::path path, mINI::INIStructure &ini)
{
    auto lastModifiedDate = fs::last_write_time(path);

    std::string &lastModifiedData = ini[path.string()]["last_modified"];

    if (lastModifiedData == fileLastWriteTimeStr(path))
    {
        LOG_INFO("file has not been modified since");
        return false;
    }
    else
    {
        LOG_INFO("file has been modified");
        return true;
    }

    return false;
}

std::string vk_deck::shader::shader_compiler::fileLastWriteTimeStr(const fs::path &path)
{
    auto ftime = fs::last_write_time(path);

    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());

    std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);

    std::string timestr = std::ctime(&cftime);
    if (!timestr.empty() && timestr.back() == '\n')
    {
        timestr.pop_back();
    }

    return timestr;
}

vk_deck::shader::shader_compiler::shader_compiler(std::string file_path) : _folder_path(std::move(file_path))
{
    // 1. Change to project root path.
    if (!changeToProjectPath())
    {
        LOG_ERROR("Project could not be found.");
        return;
    }

    LOG_INFO("Looking for folder in: {}", fs::current_path().string());

    // 2. Check if folder path exists.
    if (!fs::exists(this->_folder_path))
    {
        LOG_ERROR("Folder does not exist!");
        throw std::runtime_error("Folder does not exist");
    }

    this->_compiled_shader_folder = fs::current_path() / this->_folder_path / "compiled";
    fs::create_directory(this->_compiled_shader_folder);

    // 3. Check if ini file exists
    auto ini_path = fs::current_path() / this->_folder_path / "compiled_shaders.ini";

    if (fs::exists(ini_path))
    {
        LOG_INFO("found the ini file");
    }
    else
    {
        LOG_INFO("creating the ini file.");
        std::ofstream created_ini(ini_path);
    }

    mINI::INIFile ini_file(ini_path.string());

    mINI::INIStructure ini;

    if (!ini_file.read(ini))
    {
        LOG_ERROR("could not read ini file");
    }

    // 4. Go through shaders files and read & write
    for (const auto &file : fs::recursive_directory_iterator{this->_folder_path})
    {
        if (file.path().extension() != ".vert" && file.path().extension() != ".frag")
        {
            continue;
        }

        LOG_INFO("File: {}", file.path().string());

        if (isShaderModified(file.path(), ini))
        {
            LOG_INFO("compiling the shader again");
            ini[file.path().string()]["compiled_output"] = compileShader(file.path()).string();
            ini[file.path().string()]["last_modified"] = fileLastWriteTimeStr(file.path());
        }
        else
        {
            LOG_INFO("no compile");
        }
    }

    ini_file.write(ini);
}

vk_deck::shader::shader_compiler::~shader_compiler()
{
}
