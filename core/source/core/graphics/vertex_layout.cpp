#include "vertex_layout.hpp"

void VertexLayout::add(U32 p_count, bool p_is_normalized)
{
    m_attributes.emplace_back(VertexAttribute(p_count, p_is_normalized, m_stride));
    m_stride += sizeof(F32) * p_count;
}

U32 VertexLayout::get_stride() const
{
    return m_stride;
}

const List<VertexAttribute>& VertexLayout::get_attributes() const
{
    return m_attributes;
}
