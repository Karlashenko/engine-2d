#include "shader.hpp"

#include <glad/glad.h>

Shader::Shader(const String& p_vertex_source, const String& p_fragment_source)
{
    U32 vertex_shader_id;
    if (!try_compile_shader(p_vertex_source, GL_VERTEX_SHADER, vertex_shader_id)) {
        m_renderer_id = 0;
        return;
    }

    U32 fragment_shader_id;
    if (!try_compile_shader(p_fragment_source, GL_FRAGMENT_SHADER, fragment_shader_id)) {
        m_renderer_id = 0;
        return;
    }

    m_renderer_id = glCreateProgram();
    glAttachShader(m_renderer_id, vertex_shader_id);
    glAttachShader(m_renderer_id, fragment_shader_id);
    glLinkProgram(m_renderer_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    I32 status;
    glGetProgramiv(m_renderer_id, GL_LINK_STATUS, &status);

    if (status == GL_TRUE) {
        return;
    }

    I32 info_log_length = 0;
    glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &info_log_length);

    List<char> info_log(info_log_length);
    glGetProgramInfoLog(m_renderer_id, info_log_length, &info_log_length, &info_log[0]);
    std::cout << info_log.data() << std::endl;

    glDeleteProgram(m_renderer_id);
    m_renderer_id = 0;
}

Shader::Shader() : m_renderer_id(0)
{
}

Shader::Shader(U32 p_renderer_id) : m_renderer_id(p_renderer_id)
{
}

const RendererId& Shader::get_renderer_id() const
{
    return m_renderer_id;
}

void Shader::set_uniform_1_u(const String& p_name, U32 p_1)
{
    glUseProgram(m_renderer_id);
    glUniform1ui(get_uniform_location(p_name), p_1);
}

void Shader::set_uniform_1_i(const String& p_name, I32 p_1)
{
    glUseProgram(m_renderer_id);
    glUniform1i(get_uniform_location(p_name), p_1);
}

void Shader::set_uniform_1_f(const String& p_name, F32 p_1)
{
    glUseProgram(m_renderer_id);
    glUniform1f(get_uniform_location(p_name), p_1);
}

void Shader::set_uniform_2_f(const String& p_name, F32 p_1, F32 p_2)
{
    glUseProgram(m_renderer_id);
    glUniform2f(get_uniform_location(p_name), p_1, p_2);
}

void Shader::set_uniform_4_f(const String& p_name, F32 p_1, F32 p_2, F32 p_3, F32 p_4)
{
    glUseProgram(m_renderer_id);
    glUniform4f(get_uniform_location(p_name), p_1, p_2, p_3, p_4);
}

void Shader::set_uniform_array_i(const String& p_name, I32* p_array, U32 count)
{
    glUseProgram(m_renderer_id);
    glUniform1iv(get_uniform_location(p_name), count, p_array);
}

void Shader::set_uniform_array_u(const String& p_name, U32* p_array, U32 count)
{
    glUseProgram(m_renderer_id);
    glUniform1uiv(get_uniform_location(p_name), count, p_array);
}

void Shader::set_uniform_array_f(const String& p_name, F32* p_array, U32 count)
{
    glUseProgram(m_renderer_id);
    glUniform1fv(get_uniform_location(p_name), count, p_array);
}

void Shader::set_uniform_matrix(const String& p_name, const Matrix& p_matrix)
{
    glUseProgram(m_renderer_id);
    glUniformMatrix4fv(get_uniform_location(p_name), 1, false, &p_matrix[0][0]);
}

I32 Shader::get_uniform_location(const String& p_name)
{
    if (m_uniform_locations.find(p_name) != m_uniform_locations.end()) {
        return m_uniform_locations[p_name];
    }

    I32 location = glGetUniformLocation(m_renderer_id, p_name.c_str());

    if (location == -1) {
        std::cout << "Uniform '" << p_name << "' doesn't exist." << std::endl;
    }

    m_uniform_locations[p_name] = location;

    return location;
}

bool Shader::try_compile_shader(const String& p_source, U32 p_type, U32& p_shader_id)
{
    const GLchar* c_string = p_source.c_str();

    p_shader_id = glCreateShader(p_type);
    glShaderSource(p_shader_id, 1, &c_string, nullptr);
    glCompileShader(p_shader_id);

    I32 status;
    glGetShaderiv(p_shader_id, GL_COMPILE_STATUS, &status);

    if (status == GL_TRUE) {
        return true;
    }

    I32 info_log_length = 0;
    glGetShaderiv(p_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

    List<char> info_log(info_log_length);
    glGetShaderInfoLog(p_shader_id, info_log_length, &info_log_length, &info_log[0]);
    std::cout << info_log.data() << std::endl;

    glDeleteShader(p_shader_id);
    p_shader_id = 0;

    return false;
}
