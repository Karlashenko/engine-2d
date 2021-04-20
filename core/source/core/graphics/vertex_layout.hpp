#pragma once

#include "vertex_attribute.hpp"

class VertexLayout
{
public:
    void add(U32 p_count, bool p_is_normalized);

    [[nodiscard]] U32 get_stride() const;
    [[nodiscard]] const List<VertexAttribute>& get_attributes() const;

private:
    U32 m_stride;
    List<VertexAttribute> m_attributes;
};
