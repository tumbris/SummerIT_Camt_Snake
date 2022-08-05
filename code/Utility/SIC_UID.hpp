#pragma once

#include <Utility/Hash.hpp>

#if defined(DEBUG)
#include <string>
#endif //DEBUG

class SIC_UID
{
public:
    SIC_UID() = default;
    SIC_UID(const char* str, const size_t n = 0);
    SIC_UID(std::uint64_t hash);

    bool operator==(const SIC_UID& rhs) const;
    bool operator!=(const SIC_UID& rhs) const;

    std::uint64_t Id() const { return myHash; }
private:
    std::uint64_t myHash = 0;

#if defined(DEBUG)
public:
    SIC_UID(const std::string& str);
    const std::string& Str() const { return myString; }
private:
    std::string myString;
#endif //DEBUG
};

static constexpr uint64_t operator""_sid(const char* const str, const size_t n) noexcept
{
    return hash(str, n);
}


#include <functional>
namespace std
{
    template<> struct hash<SIC_UID> { std::size_t operator()(SIC_UID const& s) const noexcept { return s.Id(); } };
}