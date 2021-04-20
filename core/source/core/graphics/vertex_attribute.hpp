#pragma once

struct VertexAttribute
{
public:
    U32 count;
    bool is_normalized;
    U32 offset;

    VertexAttribute(U32 p_count, bool p_is_normalized, U32 p_offset)
        : count(p_count), is_normalized(p_is_normalized), offset(p_offset)
    {
    }
};
