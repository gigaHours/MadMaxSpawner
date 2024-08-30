#pragma once

#include "plugin.h"


#define HASHSTR(str) []() { static auto _hash = CHashString(str); return _hash; }()


inline SMETHOD(0x140F332C0, 0x142FBD230, uint32_t, HashString(const char* str), str)

class CHashString
{
public:
	CHashString() { m_Hash = 0; }
	CHashString(const char* str) { 
		if (str && *str)
			m_Hash = HashString(str);
		else
			m_Hash = 0;
	}
	CHashString(std::string const& str) {
		if (!str.empty())
			m_Hash = HashString(str.c_str());
		else
			m_Hash = 0;
	}
	CHashString(int hash) {
		if (hash != 0xDEADBEEF)
			m_Hash = hash;
		else
			m_Hash = 0;
	}
	CHashString(uint32_t hash) { 
		if (hash != 0xDEADBEEF)
			m_Hash = hash;
		else
			m_Hash = 0;
	}
	CHashString(CHashString const& hashS) { m_Hash = hashS.m_Hash; }
	CHashString(CHashString && hashS) noexcept { m_Hash = hashS.m_Hash; }


	uint32_t m_Hash;

	bool operator!=(CHashString const& rhs) { return m_Hash != rhs.m_Hash; }
	bool operator!=(uint32_t rhs) { return m_Hash != rhs; }
	void operator=(CHashString && rhs) noexcept { m_Hash = rhs.m_Hash; }
	void operator=(CHashString const& rhs) noexcept { m_Hash = rhs.m_Hash; }
	void operator=(const char* str) noexcept {
		if (str && *str)
			m_Hash = HashString(str);
		else
			m_Hash = 0;
	}
	bool operator==(CHashString const& rhs) { return m_Hash == rhs.m_Hash; }
	bool operator==(int rhs) { return m_Hash == rhs; }
};