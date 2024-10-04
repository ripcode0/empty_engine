#include "gl_shader.h"
#include "core/config.h"
#include "graphics/opengl/gl_config.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace emt
{

    gl_shader::gl_shader(const char *filename, shader_type type)
    {
        this->type = type;

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

        auto gl_shader_type = get_gl_shader_type(type);

        if(gl_shader_type == GL_VERTEX_SHADER){
            printf("glsl vertex\n");
        }

        if(!std::filesystem::exists(filename)){
            log_error("%s is not found", filename);
        }

        std::ifstream is(filename, std::ios::in);
        if(!is) log_error("%s unable to open", filename);

        std::stringstream code;
        code << is.rdbuf();

        is.close();
        LPCSTR _str = code.str().c_str();
        std::string code_str = code.str();
        LPCSTR str = code_str.c_str();


        program = glCreateShaderProgramv(gl_shader_type, 1, &str);

        GLint compiled{};

        glGetProgramiv(program, GL_LINK_STATUS, &compiled);

        if(compiled == GL_FALSE)
        {
            char err[512]{};
            glGetProgramInfoLog(program, 512, nullptr, err);
            char compiled_file[128]{};
            sprintf_s(compiled_file,128, "%s : %s", "compile error", filename);
            MessageBoxA(NULL, err, compiled_file, MB_OK);
            glDeleteProgram(program);
        }

    }



} // namespace emt

