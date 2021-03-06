#pragma once


template <typename T> static inline T read(DWORD_PTR base_address)
{
	T value = { 0 };
	if (base_address > 0x0000000000000000 && base_address < 0x00007fffffffffff)
	{
		__try {
			if (IsBadReadPtr((LPVOID)base_address, sizeof(value)) == 0) {
				value = *(T *)base_address;
			}
			//else {
			//	/*output_bebug_wstring(L"地址不可读");
			//	value = T();*/
			//	DWORD lpflOldProtect;
			//	VirtualProtect(LPVOID(base_address), sizeof(T), PAGE_EXECUTE_READWRITE, &lpflOldProtect);
			//	value = *(T *)base_address;
			//	VirtualProtect(LPVOID(base_address), sizeof(T), lpflOldProtect, 0);
			//}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			output_bebug_wstring(L"Read null pointer Address %x", base_address);
			return T();
		}
	}
	else {
		output_bebug_wstring(L"Read overflow Address %x", base_address);
	}
	return value;
}

template <typename T> static inline bool write(DWORD base_address,T value)
{
	bool result = true;
	if (base_address > 0x0000000000000000 && base_address < 0x00007fffffffffff)
	{
		__try {
			if (IsBadWritePtr((LPVOID)base_address, sizeof(value)) == 0) {
				*(T *)base_address = value;
			}
			//else {
			//	DWORD lpflOldProtect;
			//	VirtualProtect(LPVOID(base_address), sizeof(T), PAGE_EXECUTE_READWRITE, &lpflOldProtect);
			//	*(T *)base_address = value;
			//	VirtualProtect(LPVOID(base_address), sizeof(T), lpflOldProtect, 0);
			//	//output_bebug_wstring(L"地址不可写");
			//}
			
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			output_bebug_wstring(L"Write null pointer Address %x", base_address);
			result = false;
		}
	}
	else {
		output_bebug_wstring(L"Write overflow Address %x", base_address);
		result = false;
	}
	return result;
}

template <typename T> static inline T read_offset(DWORD_PTR base_address, std::vector<int> offset)
{
	DWORD ofset_address = read<DWORD>(base_address);
	T value;
	for (size_t i = 0; i < offset.size(); i++)
	{
		if (ofset_address > 0)
		{
			if ((i + 1) < offset.size())
			{
				ofset_address = read<DWORD>(ofset_address + offset[i]);
			}
			else {
				value = read<T>(ofset_address + offset[i]);
			}
		}
	}
	return value;
}

template <typename T> static inline bool write_offset(DWORD_PTR base_address, std::vector<int> offset, T value)
{
	DWORD ofset_address = read<DWORD>(base_address);
	bool result = false;
	
	for (size_t i = 0; i < offset.size(); i++)
	{
		if (ofset_address)
		{
			if ((i + 1) < offset.size())
			{
				ofset_address = read<DWORD>(ofset_address + offset[i]);
			}
			else {
				result = write<T>(ofset_address + offset[i], value);
			}
		}
	}
	
	return result;
}

static inline std::vector<BYTE> read_bytes(DWORD_PTR base_address,size_t length)
{
	std::vector<BYTE> bytes;
	DWORD lpflOldProtect;
	VirtualProtect(LPVOID(base_address), length, PAGE_EXECUTE_READWRITE, &lpflOldProtect);
	for (size_t i = 0; i < bytes.size(); i++)
	{
		bytes[i] = read<BYTE>(base_address + i);
	}
	VirtualProtect(LPVOID(base_address), length, lpflOldProtect, 0);
	return bytes;
}

static inline void write_bytes(DWORD_PTR base_address, std::vector<BYTE> bytes)
{
	DWORD lpflOldProtect;
	VirtualProtect((LPVOID)base_address, bytes.size(), PAGE_EXECUTE_READWRITE, &lpflOldProtect);
	for (size_t i = 0; i < bytes.size(); i++)
	{
		write<BYTE>(base_address+i, bytes[i]);
	}
	VirtualProtect((LPVOID)base_address, bytes.size(), lpflOldProtect, 0);
}


static inline std::wstring  read_wstring(DWORD_PTR base_address,size_t length)
{
	wchar_t *buffer = new wchar_t[length];
	if (IsBadReadPtr((LPVOID)base_address, length) == 0) {
		memcpy(buffer, (LPVOID)base_address, length);
	}
	std::wstring str(buffer, length);
	delete[] buffer;
	return str;
}

static inline std::string read_string(DWORD_PTR base_address, size_t length)
{
	char *buffer = new char[length];
	if (IsBadReadPtr((LPVOID)base_address, length) == 0) {
		memcpy(buffer, (LPVOID)base_address, length);
	}
	std::string str(buffer, length);
	delete[] buffer;
	return str;
}

