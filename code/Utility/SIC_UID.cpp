#include <Utility/SIC_UID.hpp>

SIC_UID::SIC_UID(const char* str, const size_t n)
	: myHash(hash(str, n ? n : strlen(str)))
#if defined(DEBUG)
	, myString(str)
#endif //DEBUG
{
}

SIC_UID::SIC_UID(std::uint64_t hash)
	: myHash(hash)
{
}

bool SIC_UID::operator==(const SIC_UID& rhs) const
{
	return myHash == rhs.myHash
#if defined(DEBUG)
		&& myString == rhs.myString
#endif //DEBUG
		;
}

bool SIC_UID::operator!=(const SIC_UID& rhs) const
{
	return !operator==(rhs);
}

#if defined(DEBUG)
SIC_UID::SIC_UID(const std::string& str)
	: myString(str)
	, myHash(hash(str.begin(), str.end()))
{
}
#endif //DEBUG