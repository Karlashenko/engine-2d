#pragma once

class Texture
{
public:
    Texture();
    Texture(U32 p_width, U32 p_height);
    Texture(U32 p_width, U32 p_height, void* p_pixels);
    Texture(U32 p_width, U32 p_height, void* p_pixels, U32 p_internal_format, U32 p_format);
    ~Texture();

    [[nodiscard]] const RendererId& get_renderer_id() const;
    [[nodiscard]] const String& get_file_path() const;
    [[nodiscard]] I32 get_width() const;
    [[nodiscard]] I32 get_height() const;
    [[nodiscard]] Vector2 get_size() const;

    bool operator==(const Texture& p_texture) const;
    bool operator!=(const Texture& p_texture) const;

private:
    RendererId m_renderer_id;
    String m_file_path;
    I32 m_width;
    I32 m_height;

    [[nodiscard]] static RendererId create_blank(U32 p_width, U32 p_height, U32 p_internal_format);
    void set_data(void* p_data, U32 p_format, U32 p_data_type) const;
};
