#include "structs.hpp"

std::string rl::unreal_engine::structs::uobject::get_object_name(bool class_name)
{
	rl::unreal_engine::structs::names_array names = *reinterpret_cast<rl::unreal_engine::structs::names_array*>(rl::addresses::names);

	if (class_name)
		return names[this->outer->name_index]->get_name() + "." + names[this->name_index]->get_name();
	else
		return names[this->name_index]->get_name();
}

rl::unreal_engine::structs::uobject* rl::unreal_engine::structs::objects_array::get_object_from_name(const char* name, const char* outer_name)
{
	for (auto i = 0; i < this->get_current_size(); ++i)
	{
		rl::unreal_engine::structs::uobject* object = this->data[i];

		if (!object)
			continue;

		const auto object_name = object->get_object_name();
		const auto outer_object_name = object->outer->get_object_name();

		if (std::strstr(object_name.c_str(), name) != 0 && std::strstr(outer_object_name.c_str(), outer_name) != 0)
			return object;
	}

	return nullptr;
}