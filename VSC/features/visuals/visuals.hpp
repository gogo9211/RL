#pragma once
#include <Windows.h>
#include <cstdint>
#include <vector>

#include "../../unreal_engine/structs/structs.hpp"

namespace rl::features::visuals
{
	struct visuals_data
	{
		std::vector<rl::unreal_engine::structs::vector> boost_positions;

		std::pair<rl::unreal_engine::structs::vector, rl::unreal_engine::structs::vector> ball_position;

		void clear()
		{
			ball_position.first = ball_position.second = { 0, 0, 0 };

			boost_positions.clear();
		}
	};

	void pre_render(rl::unreal_engine::structs::canvas* canvas);

	void draw_esp(rl::unreal_engine::structs::canvas* canvas);
}