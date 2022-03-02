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

std::pair<int, int> rl::unreal_engine::structs::canvas::get_size()
{
	const auto x = *reinterpret_cast<int*>(this->get() + rl::addresses::size_x);
	const auto y = *reinterpret_cast<int*>(this->get() + rl::addresses::size_y);

	return std::make_pair(x, y);
}

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

void rl::unreal_engine::structs::canvas::draw_line(float x1, float x2, float y1, float y2, const rl::unreal_engine::structs::color& color)
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	static auto draw_line = objects.get_object_from_name("Draw2DLine", "Canvas");

	rl::unreal_engine::arguments::draw_line args{ x1, x2, y1, y2, color };

	process_event(this, draw_line, &args);
}

void rl::unreal_engine::structs::canvas::set_draw_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	static auto set_draw_color = objects.get_object_from_name("SetDrawColor", "Canvas");

	rl::unreal_engine::arguments::set_draw_color args{ r, g, b, a };

	process_event(this, set_draw_color, &args);
}

rl::unreal_engine::structs::vector rl::unreal_engine::structs::canvas::project(rl::unreal_engine::structs::vector location)
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	static auto project = objects.get_object_from_name("Project", "Canvas");

	rl::unreal_engine::arguments::project args{ location, {} };

	process_event(this, project, &args);

	return args.out;
}

bool rl::unreal_engine::structs::vehicle_pickup::is_picked_up()
{
	auto objects = *reinterpret_cast<rl::unreal_engine::structs::objects_array*>(rl::addresses::objects);

	static auto is_picked_up = objects.get_object_from_name("IsPickedUp", "VehiclePickup_TA");

	bool ret;

	process_event(this, is_picked_up, &ret);

	return ret;
}

rl::unreal_engine::structs::vector rl::unreal_engine::structs::aactor::get_screen_pos(rl::unreal_engine::structs::canvas* canvas)
{
	const auto screen_pos = canvas->project(this->get_pos());

	if (screen_pos.z == 0)
		return {};

	return screen_pos;
}