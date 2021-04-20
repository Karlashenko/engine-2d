#pragma once

#include <array>

template<typename T, U32 size>
using Array = std::array<T, size>;

template<typename T, U32 size>
[[nodiscard]] I32 array_index_of(Array<T, size> array, const T& p_element)
{
    for (int i = 0; i < array.size(); i++) {
        if (array[i] == p_element) {
            return i;
        }
    }

    return -1;
}

template<typename T, U32 size>
[[nodiscard]] bool array_all(Array<T, size> array, bool (* predicate)(U32, const T&))
{
    for (int i = 0; i < array.size(); i++) {
        if (!predicate(i, array[i])) {
            return false;
        }
    }

    return true;
}

template<typename T, U32 size>
[[nodiscard]] bool array_any(Array<T, size> array, bool (* predicate)(U32, const T&))
{
    for (int i = 0; i < array.size(); i++) {
        if (predicate(i, array[i])) {
            return true;
        }
    }

    return false;
}

template<typename T, U32 size>
[[nodiscard]] bool array_all_equals(Array<T, size> array, const T& value)
{
    for (int i = 0; i < array.size(); i++) {
        if (array[i] != value) {
            return false;
        }
    }

    return true;
}

template<typename T, U32 size>
[[nodiscard]] bool array_any_equals(Array<T, size> array, const T& value)
{
    for (int i = 0; i < array.size(); i++) {
        if (array[i] == value) {
            return true;
        }
    }

    return false;
}
