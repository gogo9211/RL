#pragma once
#include <Windows.h>
#include <cstdint>

namespace rl::addresses
{
	const auto base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA(nullptr));
		
	const std::uint64_t names = base + 0x21FB800;
	const std::uint64_t objects = base + 0x21FB848;
	const std::uint64_t world = base + 0x220F7E8;

	const std::uint64_t process_event = base + 0x30D540;

	const std::uint64_t pickup_vtable = base + 0x1BA8530;
	const std::uint64_t ball_vtable = base + 0x1BBB1A0;

	//Offsets of World
	constexpr std::uint16_t persistent_level = 0x98;

	//Offsets of PersistentLevel
	constexpr std::uint16_t actors = 0x60;

	//Offsets of AActor
	constexpr std::uint16_t location = 0x90;

	//Offsets of VehiclePickup
	constexpr std::uint16_t fx_actor = 0x278;

	//Offsets of Canvas
	constexpr std::uint16_t size_x = 0x90;
	constexpr std::uint16_t size_y = 0x94;
}