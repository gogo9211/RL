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
		rl::unreal_engine::structs::vector in, out;
	};

	struct draw_line
	{
		float x1, x2, y1, y2;

		rl::unreal_engine::structs::color color;
	};

	struct prediction_info
	{
		float time, atp;

		rl::unreal_engine::structs::vector location, velocity, at, atv;

		std::uint32_t unk;
	};

	struct predict_position
	{
		float time;

		prediction_info info;
	};
}