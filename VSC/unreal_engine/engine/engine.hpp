#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>

#include "../structs/structs.hpp"

namespace rl::unreal_engine::engine
{
	void iterate_objects();

	void iterate_actors();

	std::uintptr_t get_world();

	std::uintptr_t get_level();

	rl::unreal_engine::structs::objects_array get_actors();

	std::string get_object_name(rl::unreal_engine::structs::uobject* object);
}