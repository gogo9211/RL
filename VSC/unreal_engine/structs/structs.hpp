#pragma once
#include <Windows.h>
#include <cstdint>
#include "../../utils/utils.hpp"
#include "../../addresses/addresses.hpp"

namespace rl::unreal_engine::structs
{
	enum { NAME_SIZE = 1024 / 4 };

	class uobject
	{
		void* vtable;

		std::uint8_t pad0[56];

		uobject* outer;

		std::uint32_t name_index;

		std::uint32_t number;

		uobject* inner;

	public:
		std::string get_object_name(bool class_name = false);

		uobject* get_outer() { return outer; }

		std::uintptr_t get() { return reinterpret_cast<std::uintptr_t>(this); }
	};

	template<class type>
	class tarray
	{
	protected:
		type* data;

	private:
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

		wchar_t name[NAME_SIZE];

	public:
		std::string get_name()
		{
			char str[NAME_SIZE];

			rl::utils::wide_to_ascii(str, name);

			return std::string{ str };
		}
	};

	struct objects_array : public tarray<uobject*>
	{
		rl::unreal_engine::structs::uobject* get_object_from_name(const char* name, const char* outer_name);
	};

	using names_array = tarray<fname_entry*>;

	struct world : public uobject
	{
		rl::unreal_engine::structs::uobject* get_level() { return *reinterpret_cast<uobject**>(this->get() + rl::addresses::persistent_level); }

		rl::unreal_engine::structs::objects_array get_actors() { return *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(get_level()->get() + rl::addresses::actors); }
	};
}