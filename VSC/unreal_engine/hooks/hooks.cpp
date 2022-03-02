#include "hooks.hpp"

#include "../../utils/utils.hpp"
#include "../../addresses/addresses.hpp"
#include "../../unreal_engine/structs/structs.hpp"

#include <vector>

static rl::unreal_engine::structs::process_event_t process_event;

rl::unreal_engine::structs::uobject* pre_render = nullptr;
rl::unreal_engine::structs::uobject* post_render = nullptr;

std::vector<rl::unreal_engine::structs::vector> boost_positions;
rl::unreal_engine::structs::vector ball_position;

void pre_render_hook(rl::unreal_engine::structs::canvas* canvas)
{
	ball_position = { 0, 0, 0 };

	boost_positions.clear();

	const auto world = *reinterpret_cast<rl::unreal_engine::structs::world**>(rl::addresses::world);

	auto actors = world->get_actors();

	for (auto i = 0; i < actors.get_current_size(); ++i)
	{
		const auto actor_obj = actors[i];

		if (!actor_obj)
			continue;

		if (*reinterpret_cast<std::uintptr_t*>(actor_obj->get()) == rl::addresses::pickup_vtable)
		{
			const auto actor = static_cast<rl::unreal_engine::structs::vehicle_pickup*>(actor_obj);

			const auto screen_pos = canvas->project(actor->get_pos());

			if (screen_pos.z == 0 || !actor->get_fx_actor() || actor->is_picked_up())
				continue;

			boost_positions.push_back(screen_pos);
		}

		if (*reinterpret_cast<std::uintptr_t*>(actor_obj->get()) == rl::addresses::ball_vtable)
		{
			const auto actor = static_cast<rl::unreal_engine::structs::aactor*>(actor_obj);

			const auto screen_pos = canvas->project(actor->get_pos());

			if (screen_pos.z == 0)
				continue;

			ball_position = screen_pos;
		}
	}
}

void post_render_hook(rl::unreal_engine::structs::canvas* canvas)
{
	const auto& [screen_x, screen_y] = canvas->get_size();

	canvas->set_pos(15, 15);
	canvas->set_draw_color(0, 255, 70, 255);
	canvas->draw_text(L"gogo1000", false, 1.f, 1.f, nullptr);

	for (const auto& pos : boost_positions)
	{
		canvas->set_pos(pos.x - 15, pos.y - 15);
		canvas->draw_box(30, 30);
	}

	if (!ball_position.is_null())
		canvas->draw_line(screen_x / 2, screen_y, ball_position.x, ball_position.y, { 0, 255, 70, 255 });
}

std::uintptr_t __fastcall process_event_hook(rl::unreal_engine::structs::uobject* object, rl::unreal_engine::structs::uobject* function, void* args)
{
	if (function == post_render)
		post_render_hook(*reinterpret_cast<rl::unreal_engine::structs::canvas**>(args));

	if (function == pre_render)
		pre_render_hook(*reinterpret_cast<rl::unreal_engine::structs::canvas**>(args));

	return process_event(object, function, args);
}

void rl::unreal_engine::hooks::init()
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	post_render = objects.get_object_from_name("PostRender", "GameViewportClient");
	pre_render = objects.get_object_from_name("PreRender", "PlayerController");

	process_event = rl::utils::tramp_hook<rl::unreal_engine::structs::process_event_t>(reinterpret_cast<void*>(rl::addresses::process_event), process_event_hook, 18);
}