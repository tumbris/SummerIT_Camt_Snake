#pragma once

#include <cstdint>

namespace details
{
    namespace fnv
    {
        constexpr static std::uint64_t FNV_OFFSET_BASIS   = 0xcbf29ce484222325;
        constexpr static std::uint64_t FNV_PRIME          = 0x00000100000001B3;

        template <class Iter>
        constexpr std::uint64_t fnv1_hash(Iter begin, Iter end)
        {
            std::uint64_t hash = FNV_OFFSET_BASIS;
            for (auto head = begin; head != end; ++head)
            {
                hash *= FNV_PRIME;
                hash ^= *head;
            }
            return hash;
        }

        template <class Iter>
        constexpr std::uint64_t fnv1_hash(Iter begin, size_t n) noexcept
        {
            std::uint64_t hash = FNV_OFFSET_BASIS;
            for (size_t i = 0; i < n; ++i, ++begin)
            {
                hash *= FNV_PRIME;
                hash ^= *begin;
            }
            return hash;
        }

        template <class Iter>
        constexpr std::uint64_t fnv1a_hash(Iter begin, Iter end)
        {
            std::uint64_t hash = FNV_OFFSET_BASIS;
            for (auto head = begin; head != end; ++head)
            {
                hash ^= *head;
                hash *= FNV_PRIME;
            }
            return hash;
        }

        template <class Iter>
        constexpr std::uint64_t fnv1a_hash(Iter begin, size_t n) noexcept
        {
            std::uint64_t hash = FNV_OFFSET_BASIS;
            for (size_t i = 0; i < n; ++i, ++begin)
            {
                hash ^= *begin;
                hash *= FNV_PRIME;
            }
            return hash;
        }
    }

    template <class Iter>
    constexpr std::uint64_t DefaultHasher(Iter begin, Iter end)
    {
        return fnv::fnv1a_hash(begin, end);
    }

    template <class Iter>
    constexpr std::uint64_t DefaultHasher(Iter begin, size_t n)
    {
        return fnv::fnv1a_hash(begin, n);
    }
}

template <class Iter>
static constexpr std::uint64_t hash(Iter begin, Iter end) noexcept
{
    return details::DefaultHasher(begin, end);
}

template <class Iter>
static constexpr std::uint64_t hash(Iter bytes, size_t n) noexcept
{
    return details::DefaultHasher(bytes, n);
}