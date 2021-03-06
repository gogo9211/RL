#pragma once
#include <Windows.h>
#include <cstdint>

namespace rl::addresses
{
	const auto base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA(nullptr));
		
	const std::uint64_t names = base + 0x22059C0;
	const std::uint64_t objects = base + 0x2205A08;
	const std::uint64_t world = base + 0x2219960;
	const std::uint64_t engine = base + 0x2215510;

	const std::uint64_t process_event = base + 0x314ED0;

	const std::uint64_t pickup_vtable = base + 0x1BB2270;
	const std::uint64_t ball_vtable = base + 0x1BC5168;

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

	//Offsets of Engine
	constexpr std::uint16_t local_player = 0x760;

	//Offsets of LocalPlayer
	constexpr std::uint16_t player_controller = 0x78;

	//Offsets of PlayerController
	constexpr std::uint16_t pawn = 0x4A0;
}