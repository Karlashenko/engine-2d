#pragma once

#include <memory>
#include <utility>

template<typename T>
using Shared = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Shared<T> create_shared(Args&& ...p_args)
{
    return std::make_shared<T>(std::forward<Args>(p_args)...);
}

template<typename TTarget, typename TObject>
constexpr Shared<TTarget> convert_shared(TObject p_object)
{
    return std::static_pointer_cast<TTarget>(p_object);
}
