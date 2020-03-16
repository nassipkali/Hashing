#pragma once

#ifndef PLATFORM_HASHING_HASH
#define PLATFORM_HASHING_HASH

namespace Platform::Hashing
{
    template <typename T, typename = std::void_t<>>
    struct is_std_hashable : std::false_type { };

    template <typename T>
    struct is_std_hashable<T, std::void_t<decltype(std::declval<std::hash<T>>()(std::declval<T>()))>> : std::true_type { };

    template<typename T> std::size_t Hash(T &&value)
    {
        if constexpr (is_std_hashable<T>::value)
        {
            std::hash<T> hasher;
            return static_cast<std::uint32_t>(hasher(value));
        }
        else
        {
            std::uint32_t hash = 0;
            Combine(hash, value);
            return Expand(hash);
        }
    }

    template<typename ... Args> std::size_t Hash(Args... args)
    {
        std::tuple<Args...> argsTuple = { args... };
        std::hash<std::tuple<Args...>> hasher;
        return static_cast<std::size_t>(hasher(argsTuple));
    }
}

#endif
