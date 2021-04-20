#pragma once

#include "../io/file_system.hpp"
#include "shader.hpp"
#include "texture.hpp"

class Graphics
{
public:
    explicit Graphics(Shared<FileSystem> p_file_system);

    [[nodiscard]] U32 get_max_texture_units() const;
    [[nodiscard]] Shared<Shader> create_shader(const String& p_vert_file_path, const String& p_frag_file_path) const;
    [[nodiscard]] Shared<Texture> create_texture(const String& p_file_path) const;

private:
    Shared<FileSystem> m_file_system;
    I32 m_max_texture_units;
};
