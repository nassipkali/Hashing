#pragma once

#ifndef PLATFORM_HASHING_EXPAND
#define PLATFORM_HASHING_EXPAND

// Based on https://security.stackexchange.com/a/209892

namespace Platform::Hashing
{
    std::size_t Expand(std::uint32_t originalHash)
    {
        if constexpr (sizeof(std::size_t) > sizeof(std::uint32_t))
        {
            std::uint32_t additionalHash = 0;
            Combine(additionalHash, originalHash);
            Combine(additionalHash, additionalHash ^ originalHash);
            std::size_t hash = static_cast<std::size_t>(originalHash) | (static_cast<std::size_t>(additionalHash) << (sizeof(std::uint32_t) * 8));
            return hash;
        }
        else
        {
            return originalHash;
        }
    }
}

#endif
