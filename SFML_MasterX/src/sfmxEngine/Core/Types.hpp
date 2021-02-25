#pragma once

#include "PCH/sfmxpch.hpp"

namespace masterX
{
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ...Args>
    Ref<T> createRef(Args&& ...args)
    {
        return std::make_shared<T>(args...);
    }
}