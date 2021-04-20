#pragma once

#include <vector>

template<typename T>
using List = std::vector<T>;

template<typename T>
[[nodiscard]] List<T> list_create_range(U32 p_from, U32 p_to)
{
    U32 count = p_to - p_from;
    U32 index = 0;

    List<T> array = List<T>(count);

    for (U32 i = p_from; i < p_to; i++) {
        array[index] = i;
        index += 1;
    }

    return array;
}

template<typename T>
[[nodiscard]] I32 list_index_of(const List<T>& p_list, const T& p_element)
{
    for (int i = 0; i < p_list.size(); i++) {
        if (p_list[i] == p_element) {
            return i;
        }
    }

    return -1;
}

template<typename T>
void list_remove(List<T>& p_list, const T& p_element)
{
    p_list.erase(std::remove(p_list.begin(), p_list.end(), p_element), p_list.end());
}
