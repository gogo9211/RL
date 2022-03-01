#include "structs.hpp"

#include "../function_arguments/function_arguments.hpp"

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
		const auto outer_object = object->get_outer();

		if (!outer_object)
			continue;

		const auto outer_object_name = outer_object->get_object_name();

		if (std::strstr(object_name.c_str(), name) != 0 && std::strstr(outer_object_name.c_str(), outer_name) != 0)
			return object;
	}

	return nullptr;
}

static rl::unreal_engine::structs::process_event_t process_event = reinterpret_cast<rl::unreal_engine::structs::process_event_t>(rl::addresses::process_event);

void rl::unreal_engine::structs::canvas::draw_box(float width, float heigth)
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	static auto draw_box = objects.get_object_from_name("DrawBox", "Canvas");

	rl::unreal_engine::arguments::draw_box args{ width, heigth };

	process_event(this, draw_box, &args);
}

void rl::unreal_engine::structs::canvas::set_pos(float x, float y, float z)
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	static auto set_pos = objects.get_object_from_name("SetPos", "Canvas");

	rl::unreal_engine::arguments::set_position args{ x, y, z };

	process_event(this, set_pos, &args);
}

void rl::unreal_engine::structs::canvas::draw_text(const rl::unreal_engine::structs::fstring& text, bool cr, float x, float y, void* unk)
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	static auto draw_text = objects.get_object_from_name("DrawText", "Canvas");

	rl::unreal_engine::arguments::draw_text args{ text, cr, x, y, unk };

	process_event(this, draw_text, &args);
}

void rl::unreal_engine::structs::canvas::set_draw_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	static auto set_draw_color = objects.get_object_from_name("SetDrawColor", "Canvas");

	rl::unreal_engine::arguments::set_draw_color args{ r, g, b, a };

	process_event(this, set_draw_color, &args);
}