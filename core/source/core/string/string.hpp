#pragma once

#include <string>
#include <memory>
#include "../numerics/numbers.hpp"

using String = std::string;

template<typename... Args>
String string_format(const String& format, Args... args)
{
    int size = snprintf(nullptr, 0, format.c_str(), args...) + 1;

    std::unique_ptr<char[]> buffer(new char[size]);
    snprintf(buffer.get(), size, format.c_str(), args...);

    return String(buffer.get(), buffer.get() + size - 1);
}
