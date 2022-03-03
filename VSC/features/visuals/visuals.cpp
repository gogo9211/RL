#include "visuals.hpp"

rl::features::visuals::visuals_data visual_data;

void rl::features::visuals::pre_render(rl::unreal_engine::structs::canvas* canvas)
{
	visual_data.clear();

	const auto world = *reinterpret_cast<rl::unreal_engine::structs::world**>(rl::addresses::world);

	auto actors = world->get_actors();

	for (auto i = 0; i < actors.get_current_size(); ++i)
	{
		const auto actor_obj = actors[i];

		if (!actor_obj)
			continue;

		const auto actor_vtable = *reinterpret_cast<std::uintptr_t*>(actor_obj->get());

		if (actor_vtable == rl::addresses::pickup_vtable)
		{
			const auto actor = static_cast<rl::unreal_engine::structs::vehicle_pickup*>(actor_obj);

			auto screen_pos = actor->get_screen_pos(canvas);

			if (screen_pos.is_null() || !actor->get_fx_actor() || actor->is_picked_up())
				continue;

			visual_data.boost_positions.push_back(screen_pos);
		}

		else if (actor_vtable == rl::addresses::ball_vtable)
		{
			const auto actor = static_cast<rl::unreal_engine::structs::ball*>(actor_obj);

			const auto screen_pos_predicted = canvas->project(actor->predict_position(1.f));

			auto screen_pos = actor->get_screen_pos(canvas);

			if (screen_pos_predicted.z == 0 || screen_pos.is_null())
				continue;

			visual_data.ball_position = std::make_pair(screen_pos, screen_pos_predicted);
		}
	}
}

void rl::features::visuals::draw_esp(rl::unreal_engine::structs::canvas* canvas)
{
	const auto& [screen_x, screen_y] = canvas->get_size();

	canvas->set_pos(15, 15);
	canvas->set_draw_color(0, 255, 70, 255);
	canvas->draw_text(L"gogo1000", false, 1.f, 1.f, nullptr);

	for (const auto& pos : visual_data.boost_positions)
	{
		canvas->set_pos(pos.x - 15, pos.y - 15);
		canvas->draw_box(30, 30);
	}

	if (!visual_data.ball_position.first.is_null() && !visual_data.ball_position.second.is_null())
	{
		canvas->draw_line(screen_x / 2, screen_y, visual_data.ball_position.first.x, visual_data.ball_position.first.y, { 0, 255, 70, 255 });
		canvas->set_pos(visual_data.ball_position.second.x - 8, visual_data.ball_position.second.y - 8);
		canvas->draw_box(16, 16);
	}
}