#include "engine.hpp"

#include "../../addresses/addresses.hpp"

#include <iostream>

void rl::unreal_engine::engine::iterate_objects()
{
	rl::unreal_engine::structs::objects_array objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);
	rl::unreal_engine::structs::names_array names = *reinterpret_cast<rl::unreal_engine::structs::names_array*>(rl::addresses::names);

	std::printf("Objects: 0x%016llx\n", rl::addresses::objects);
	std::printf("Names: 0x%016llx\n", rl::addresses::names);
	std::printf("World: 0x%016llx\n\n", rl::addresses::world);

	std::printf("Current Size: %i\n", objects.get_current_size());
	std::printf("Max Size: %i\n\n", objects.get_max_size());

	std::printf("First Object: 0x%p | Name: %s\n", objects[0], get_object_name(objects[0]).c_str());
	std::printf("First Name: %s\n\n", names[0]->get_name().c_str());
}

void rl::unreal_engine::engine::iterate_actors()
{
	auto actors = rl::unreal_engine::engine::get_actors();

	for (auto i = 0; i < actors.get_current_size(); ++i)
	{
		const auto actor = actors[i];

		if (!actor)
			continue;

		if (*reinterpret_cast<std::uintptr_t*>(actor->get()) == rl::addresses::ball_vtable || *reinterpret_cast<std::uintptr_t*>(actor->get()) == rl::addresses::pickup_vtable)
			std::printf("Actor: 0x%p | Name: %s\n", actor, get_object_name(actor).c_str());
	}
}

std::uintptr_t rl::unreal_engine::engine::get_world()
{
	return *reinterpret_cast<std::uintptr_t*>(rl::addresses::world);
}

std::uintptr_t rl::unreal_engine::engine::get_level()
{
	const auto world = rl::unreal_engine::engine::get_world();

	if (!world)
		return {};

	return *reinterpret_cast<std::uintptr_t*>(world + rl::addresses::persistent_level);
}

rl::unreal_engine::structs::objects_array rl::unreal_engine::engine::get_actors()
{
	const auto level = rl::unreal_engine::engine::get_level();

	if (!level)
		return {};

	return *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(level + rl::addresses::actors);
}

std::string rl::unreal_engine::engine::get_object_name(rl::unreal_engine::structs::uobject* object)
{
	rl::unreal_engine::structs::names_array names = *reinterpret_cast<rl::unreal_engine::structs::names_array*>(rl::addresses::names);

	const auto name_index = object->name_index;

	return names[name_index]->get_name();
}