#pragma once

class Shader
{
public:
    Shader();
    explicit Shader(U32 p_renderer_id);
    Shader(const String& p_vertex_source, const String& p_fragment_source);

    [[nodiscard]] const RendererId& get_renderer_id() const;

    void set_uniform_1_u(const String& p_name, U32 p_1);
    void set_uniform_1_i(const String& p_name, I32 p_1);
    void set_uniform_1_f(const String& p_name, F32 p_1);
    void set_uniform_2_f(const String& p_name, F32 p_1, F32 p_2);
    void set_uniform_4_f(const String& p_name, F32 p_1, F32 p_2, F32 p_3, F32 p_4);
    void set_uniform_array_i(const String& p_name, I32* p_array, U32 count);
    void set_uniform_array_u(const String& p_name, U32* p_array, U32 count);
    void set_uniform_array_f(const String& p_name, F32* p_array, U32 count);
    void set_uniform_matrix(const String& p_name, const Matrix& p_matrix);

private:
    RendererId m_renderer_id;
    HashMap<String, I32> m_uniform_locations;

    I32 get_uniform_location(const String& p_name);

    static bool try_compile_shader(const String& p_source, U32 p_type, U32& p_shader_id);
};
