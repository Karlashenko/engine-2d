#pragma once

#include "../collections/list.hpp"

class FileSystem final
{
public:
    explicit FileSystem(String p_root);

    [[nodiscard]] String get_full_path(const String& p_path) const;

    [[nodiscard]] List<U8> read_bytes(const String& p_path) const;

    [[nodiscard]] String read_string(const String& p_path) const;

private:
    String m_root;
};
