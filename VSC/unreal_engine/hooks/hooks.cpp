#include "hooks.hpp"

#include "../../utils/utils.hpp"
#include "../../unreal_engine/structs/structs.hpp"
#include "../../features/visuals/visuals.hpp"

#include <vector>

static rl::unreal_engine::structs::process_event_t process_event;

rl::unreal_engine::structs::uobject* pre_render = nullptr;
rl::unreal_engine::structs::uobject* post_render = nullptr;

std::uintptr_t __fastcall process_event_hook(rl::unreal_engine::structs::uobject* object, rl::unreal_engine::structs::uobject* function, void* args)
{
	if (function == pre_render)
		rl::features::visuals::pre_render(*reinterpret_cast<rl::unreal_engine::structs::canvas**>(args));

	if (function == post_render)
		rl::features::visuals::draw_esp(*reinterpret_cast<rl::unreal_engine::structs::canvas**>(args));

	return process_event(object, function, args);
}

void rl::unreal_engine::hooks::init()
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	post_render = objects.get_object_from_name("PostRender", "GameViewportClient");
	pre_render = objects.get_object_from_name("PreRender", "PlayerController");

	process_event = rl::utils::tramp_hook<rl::unreal_engine::structs::process_event_t>(reinterpret_cast<void*>(rl::addresses::process_event), process_event_hook, 18);
}