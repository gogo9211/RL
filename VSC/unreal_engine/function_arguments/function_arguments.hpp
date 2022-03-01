#pragma once
#include <Windows.h>
#include <cstdint>

#include "../structs/structs.hpp"

namespace rl::unreal_engine::arguments
{
	struct draw_box
	{
		float width;

		float heigth;
	};

	struct set_position
	{
		float x;

		float y;

		float z;
	};

	struct draw_text
	{
		rl::unreal_engine::structs::fstring text;

		bool cr;

		float x;

		float y;

		void* unk;
	};

	struct set_draw_color
	{
		unsigned char r;

		unsigned char g;

		unsigned char b;

		unsigned char a;
	};
}