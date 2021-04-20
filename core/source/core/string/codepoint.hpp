#pragma once

class Codepoint final
{
public:
    static const U32 c_null = 0;
    static const U32 c_tab = 9;
    static const U32 c_new_line = 10;
    static const U32 c_space = 32;

private:
    Codepoint() = default;
};
