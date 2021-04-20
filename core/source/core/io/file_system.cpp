#include "file_system.hpp"

#include <fstream>

FileSystem::FileSystem(String p_root) : m_root(std::move(p_root))
{
}

String FileSystem::get_full_path(const String& p_path) const
{
    return m_root + "/" + p_path;
}

List<U8> FileSystem::read_bytes(const String& p_path) const
{
    std::ifstream stream(m_root + "/" + p_path, std::ios::binary);

    if (!stream.is_open()) {
        exit(EXIT_FAILURE);
    }

    return List<U8>(
        std::istreambuf_iterator<char>(stream),
        std::istreambuf_iterator<char>()
    );
}

String FileSystem::read_string(const String& p_path) const
{
    std::ifstream stream(m_root + "/" + p_path);

    if (!stream.is_open()) {
        exit(EXIT_FAILURE);
    }

    return String(
        std::istreambuf_iterator<char>(stream),
        std::istreambuf_iterator<char>()
    );
}
