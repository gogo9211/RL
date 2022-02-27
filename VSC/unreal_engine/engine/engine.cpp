#include "engine.hpp"

#include "../../addresses/addresses.hpp"

#include <iostream>

void rl::unreal_engine::engine::iterate_objects()
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	std::printf("Objects: 0x%016llx\n", rl::addresses::objects);
	std::printf("Names: 0x%016llx\n", rl::addresses::names);
	std::printf("World: 0x%016llx\n\n", rl::addresses::world);

	std::printf("Current Size: %i\n", objects.get_current_size());
	std::printf("Max Size: %i\n\n", objects.get_max_size());

	std::printf("First Object: 0x%p | Name: %s\n", objects[0], objects[0]->get_object_name().c_str());
	
	const auto pre_render = objects.get_object_from_name("PreRender", "PlayerController");
	const auto pre_render_name = pre_render->get_object_name(true);

	std::printf("PreRender: %p | %s\n\n", pre_render, pre_render_name.c_str());
}

void rl::unreal_engine::engine::iterate_actors()
{
	const auto world = *reinterpret_cast<rl::unreal_engine::structs::world**>(rl::addresses::world);

	auto actors = world->get_actors();

	for (auto i = 0; i < actors.get_current_size(); ++i)
	{
		const auto actor = actors[i];

		if (!actor)
			continue;

		std::printf("Actor: 0x%p | Name: %s\n", actor, actor->get_object_name().c_str());
	}
}