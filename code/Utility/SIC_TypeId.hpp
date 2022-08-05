#pragma once

#include <cstdint>

struct SIC_TypeId
{
	template <class T>
	static SIC_TypeId Get()
	{
		return SIC_TypeId{ GetTypeIdInternal<T>() };
	}

	template <class T> bool Is() const { return operator==(SIC_TypeId::Get<T>()); }

	bool operator ==(const SIC_TypeId& other) const { return myTypeId == other.myTypeId; }
	bool operator !=(const SIC_TypeId& other) const { return !operator==(other); }

	std::uint64_t myTypeId;

private:
	static std::uint64_t ourTypeCounter;
	template <class T> static std::uint64_t GetTypeIdInternal() { static auto id = ourTypeCounter++; return id; }
};