#include <Windows.h>
#include <thread>

#include "unreal_engine/engine/engine.hpp"

int d_main()
{
	AllocConsole();

	FILE* file_stream;

	freopen_s(&file_stream, "CONIN$", "r", stdin);
	freopen_s(&file_stream, "CONOUT$", "w", stdout);
	freopen_s(&file_stream, "CONOUT$", "w", stderr);

	fclose(file_stream);

	SetConsoleTitleA("RL");

	rl::unreal_engine::engine::iterate_objects();

	return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		std::thread{ d_main }.detach();

	return TRUE;
}