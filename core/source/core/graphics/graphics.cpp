#include "graphics.hpp"
#include <glad/glad.h>

#include <utility>
#include <stb_image.h>

void APIENTRY gl_debug_message_callback(GLenum p_source, GLenum p_type, GLuint p_id, GLenum p_severity, GLsizei p_length, const GLchar* p_message, const void* p_user_param)
{
    std::cout << "OpenGL Debug [" << p_source << " " << p_type << " " << p_id << " " << p_severity << "]:\n\n" << p_message << std::endl << std::endl;
}

Graphics::Graphics(Shared<FileSystem> p_file_system) : m_file_system(std::move(p_file_system)), m_max_texture_units(0)
{
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << String((const char*) glGetString(GL_VERSION)) << std::endl;

    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &m_max_texture_units);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(gl_debug_message_callback, nullptr);
}

U32 Graphics::get_max_texture_units() const
{
    return m_max_texture_units;
}

Shared<Shader> Graphics::create_shader(const String& p_vert_file_path, const String& p_frag_file_path) const
{
    auto vert_source = m_file_system->read_string(p_vert_file_path);
    auto frag_source = m_file_system->read_string(p_frag_file_path);

    frag_source = std::regex_replace(frag_source, std::regex("u_Textures\\[(.+)\\];"), string_format("u_Textures[%d];", m_max_texture_units));

    Shared<Shader> shader = create_shared<Shader>(vert_source, frag_source);
    shader->set_uniform_array_i("u_Textures", list_create_range<I32>(0, m_max_texture_units).data(), m_max_texture_units);

    return shader;
}

Shared<Texture> Graphics::create_texture(const String& p_file_path) const
{
    I32 width;
    I32 height;
    I32 channels;

    stbi_set_flip_vertically_on_load(1);

    U8* pixels = stbi_load(m_file_system->get_full_path(p_file_path).c_str(), &width, &height, &channels, STBI_rgb_alpha);

    Shared<Texture> texture = create_shared<Texture>(width, height, pixels);

    stbi_image_free(pixels);

    return texture;
}
