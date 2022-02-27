#pragma once
#include <Windows.h>
#include <cstdint>
#include "../../utils/utils.hpp"

namespace rl::unreal_engine::structs
{
	struct uobject
	{
		void* vtable;

		std::uint8_t pad0[56];

		std::uintptr_t outer;

		std::uint32_t name_index;

		std::uintptr_t get() { return reinterpret_cast<std::uintptr_t>(this); }
	};

	template<class type>
	class tarray
	{
		type* data;

		std::uint32_t current_size;

		std::uint32_t max_size;

	public:
		std::uint32_t get_current_size() { return current_size; }

		std::uint32_t get_max_size() { return max_size; }

		type& operator[](std::uint32_t index) { return data[index]; }
	};

	class fname_entry
	{
		std::uint8_t pad0[0x8];

		std::uint32_t index;

		std::uint8_t pad1[0xC];

		wchar_t name[100];

	public:
		std::string get_name()
		{
			char str[100];

			rl::utils::wide_to_ascii(str, name);

			return std::string{ str };
		}
	};

	using objects_array = tarray<uobject*>;
	using names_array = tarray<fname_entry*>;
}