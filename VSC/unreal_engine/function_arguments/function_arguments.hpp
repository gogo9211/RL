#pragma once
#include <Windows.h>
#include <cstdint>

#include "../structs/structs.hpp"

namespace rl::unreal_engine::arguments
{
	struct draw_box
	{
		float width, heigth;
	};

	struct set_position
	{
		float x, y, z;
	};

	struct draw_text
	{
		rl::unreal_engine::structs::fstring text;

		bool cr;

		float x, y;

		void* unk;
	};

	struct set_draw_color
	{
		unsigned char r, g, b, a;
	};

	struct project
	{
		rl::unreal_engine::structs::vector in;

		rl::unreal_engine::structs::vector out;
	};
}