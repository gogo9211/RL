#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>

namespace rl::utils
{
	void wide_to_ascii(char* const buffer, const wchar_t* const wide_char);

	template<class type>
	type tramp_hook(void* func_ptr, const void* new_func, std::size_t inst_size)
	{
		constexpr auto extra_size = 12;

		auto new_func_n = reinterpret_cast<std::uintptr_t>(new_func);
		auto func_n = reinterpret_cast<std::uintptr_t>(func_ptr);

		auto clone = reinterpret_cast<std::uintptr_t>(VirtualAlloc(nullptr, inst_size + extra_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));

		if (!clone)
			return 0;

		std::memmove(reinterpret_cast<void*>(clone), func_ptr, inst_size);

		std::uint8_t jmp[] = { 0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0xC3 };

		std::memcpy(reinterpret_cast<void*>(clone + inst_size), jmp, sizeof(jmp));

		*reinterpret_cast<std::uintptr_t*>(clone + inst_size + 2) = func_n + inst_size;

		DWORD old_protect{ 0 };

		VirtualProtect(func_ptr, inst_size, PAGE_EXECUTE_READWRITE, &old_protect);

		std::memset(func_ptr, 0x90, inst_size);
		std::memcpy(func_ptr, jmp, sizeof(jmp));

		*reinterpret_cast<std::uintptr_t*>(func_n + 2) = new_func_n;

		VirtualProtect(func_ptr, inst_size, old_protect, &old_protect);

		return reinterpret_cast<type>(clone);
	}
}