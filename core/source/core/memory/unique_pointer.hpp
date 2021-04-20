#pragma once

#include <memory>
#include <utility>

template<typename T>
using Unique = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Unique<T> create_unique(Args&& ...p_args)
{
    return std::make_unique<T>(std::forward<Args>(p_args)...);
}

template<typename TTarget, typename TObject>
constexpr Unique<TTarget> convert_unique(TObject p_object)
{
    return std::static_pointer_cast<TTarget>(p_object);
}
