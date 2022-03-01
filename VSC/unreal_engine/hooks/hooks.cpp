#include "hooks.hpp"

#include "../../utils/utils.hpp"
#include "../../addresses/addresses.hpp"
#include "../../unreal_engine/structs/structs.hpp"

static rl::unreal_engine::structs::process_event_t process_event;

rl::unreal_engine::structs::uobject* post_render = nullptr;

void post_render_hook(rl::unreal_engine::structs::canvas* canvas)
{
	std::printf("PostRender Called! Arg: %p | %s\n", canvas, canvas->get_object_name().c_str());

	canvas->set_pos(15, 15);
	canvas->set_draw_color(0, 255, 70, 255);
	canvas->draw_text(L"gogo1000", false, 1.f, 1.f, nullptr);
}

std::uintptr_t __fastcall process_event_hook(rl::unreal_engine::structs::uobject* object, rl::unreal_engine::structs::uobject* function, void* args)
{
	if (*reinterpret_cast<std::uintptr_t*>(object->get()) == rl::addresses::viewport_vtable && function == post_render)
		post_render_hook(*reinterpret_cast<rl::unreal_engine::structs::canvas**>(args));

	return process_event(object, function, args);
}

void rl::unreal_engine::hooks::init()
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	post_render = objects.get_object_from_name("PostRender", "GameViewportClient");

	process_event = rl::utils::tramp_hook<rl::unreal_engine::structs::process_event_t>(reinterpret_cast<void*>(rl::addresses::process_event), process_event_hook, 18);
}