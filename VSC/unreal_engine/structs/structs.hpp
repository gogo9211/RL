#pragma once
#include <Windows.h>
#include <cstdint>

#include "../../utils/utils.hpp"
#include "../../addresses/addresses.hpp"

namespace rl::unreal_engine::structs
{
	enum { NAME_SIZE = 1024 / 4 };

	struct vector
	{
		float x, y, z;

		bool is_null() { return x == 0 && y == 0 && z == 0; }
	};

	struct color
	{
		unsigned char R, G, B, A;
	};

	class uobject
	{
		void* vtable;

		std::uint8_t pad0[56];

		uobject* outer;

		std::uint32_t name_index;

	public:
		std::string get_object_name(bool class_name = false);

		uobject* get_outer() { return outer; }

		std::uintptr_t get() { return reinterpret_cast<std::uintptr_t>(this); }
	};

	using process_event_t = std::uintptr_t(__fastcall*)(rl::unreal_engine::structs::uobject* object, rl::unreal_engine::structs::uobject* function, void* args);

	template<class type>
	class tarray
	{
		friend struct fstring;

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

	struct fstring : tarray<wchar_t>
	{
		fstring(const wchar_t* str)
		{
			current_size = std::wcslen(str) + 1;
			max_size = current_size;

			data = const_cast<wchar_t*>(str);
		};
	};

	using names_array = tarray<fname_entry*>;

	struct objects_array : tarray<uobject*>
	{
		rl::unreal_engine::structs::uobject* get_object_from_name(const char* name, const char* outer_name);
	};

	struct world : uobject
	{
		rl::unreal_engine::structs::uobject* get_level() { return *reinterpret_cast<uobject**>(this->get() + rl::addresses::persistent_level); }

		rl::unreal_engine::structs::objects_array get_actors() { return *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(get_level()->get() + rl::addresses::actors); }
	};

	struct canvas : uobject
	{
		std::pair<int, int> get_size();

		void draw_box(float width, float heigth);

		void set_pos(float x, float y, float z = 1.f);

		void draw_text(const rl::unreal_engine::structs::fstring& text, bool cr, float x, float y, void* unk);

		void set_draw_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		void draw_line(float x1, float x2, float y1, float y2, const rl::unreal_engine::structs::color& color);

		rl::unreal_engine::structs::vector project(rl::unreal_engine::structs::vector location);
	};

	struct aactor : uobject
	{
		rl::unreal_engine::structs::vector get_pos() { return *reinterpret_cast<rl::unreal_engine::structs::vector*>(this->get() + rl::addresses::location); }

		rl::unreal_engine::structs::vector get_screen_pos(rl::unreal_engine::structs::canvas* canvas);
	};

	struct vehicle_pickup : aactor
	{
		rl::unreal_engine::structs::uobject* get_fx_actor() { return *reinterpret_cast<uobject**>(this->get() + rl::addresses::fx_actor); }

		bool is_picked_up();
	};
}