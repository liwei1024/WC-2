#pragma once


template <typename T> inline T read(DWORD base_address)
{
	T value;
	__try {
		value = *(T*)base_address;
	}
	__except (1) {
		value = T();
	}
	return value;
}

template <typename T> inline bool write(DWORD base_address,T value)
{
	__try {
		*(T*)base_address = value;
		return true;
	}
	__except (1) {
		return false;
	}
}

template <typename T> inline T read_offset(DWORD base_address, std::vector<DWORD> offset)
{

}

template <typename T> inline bool write_offset(DWORD base_address, std::vector<DWORD> offset, T value)
{

}

inline bool read_bytes(DWORD base_address,size_t length, std::vector<BYTE> &bytes)
{

}

inline bool write_bytes(DWORD base_address, std::vector<BYTE> bytes)
{
	return true;
}


inline std::wstring  read_wstring(DWORD base_address,size_t length)
{

}

inline std::string read_string(DWORD base_address, size_t length)
{

}

