#include "gl_shader.h"
#include "core/config.h"
#include "graphics/opengl/gl_config.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace emt
{
    uint compile_from_file(const char* filename, shader_type type){
        static auto get_gl_shader_type = [](shader_type type){
            switch (type)
            {
            case shader_type::vertex: return GL_VERTEX_SHADER;
            case shader_type::pixel: return GL_FRAGMENT_SHADER;
            case shader_type::geometry: return GL_GEOMETRY_SHADER;
            case shader_type::hull: return GL_TESS_CONTROL_SHADER;
            case shader_type::compute: return GL_COMPUTE_SHADER;
            }
            return 0;
        };

        uint gpu_shader_id = 0;
        auto gl_shader_type = get_gl_shader_type(type);

        if(gl_shader_type == GL_VERTEX_SHADER){
            printf("glsl vertex\n");
        }

        if(!std::filesystem::exists(filename)){
            log_error("%s is not found", filename);
        }

        std::ifstream is(filename, std::ios::in);
        if(!is) {
            log_error("%s unable to open", filename);
        }

        std::string code((std::istreambuf_iterator<char>(is)),
                          std::istreambuf_iterator<char>());

        is.close();

        const char* code_str = code.c_str();
        gpu_shader_id = glCreateShaderProgramv(gl_shader_type, 1, &code_str);

        GLint compiled{};

        glGetProgramiv(gpu_shader_id, GL_LINK_STATUS, &compiled);

        if(compiled == GL_FALSE)
        {
            char err[512]{};
            glGetProgramInfoLog(gpu_shader_id, 512, nullptr, err);
            char compiled_file[128]{};
            sprintf_s(compiled_file,128, "%s : %s", "compile error", filename);
            MessageBoxA(NULL, err, compiled_file, MB_OK);
            glDeleteProgram(gpu_shader_id);
        }
        return gpu_shader_id;
    }

    gl_vertex_shader::gl_vertex_shader(const char *filename)
    {
        gpu_shader_id = compile_from_file(filename, this->type);
    }

    gl_vertex_shader::~gl_vertex_shader()
    {
        
        if(gpu_shader_id) glDeleteProgram(gpu_shader_id);
    }

    gl_pixel_shader::gl_pixel_shader(const char *filename)
    {
        gpu_shader_id = compile_from_file(filename, this->type);
    }

    gl_pixel_shader::~gl_pixel_shader()
    {
        if(gpu_shader_id) glDeleteProgram(gpu_shader_id);
    }

    gl_geometry_shader::gl_geometry_shader(const char *filename)
    {
        gpu_shader_id = compile_from_file(filename, this->type);
    }

    gl_geometry_shader::~gl_geometry_shader()
    {
        if(gpu_shader_id) glDeleteProgram(gpu_shader_id);
    }

} // namespace emt
