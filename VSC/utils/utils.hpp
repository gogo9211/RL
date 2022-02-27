#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>

namespace rl::utils
{
	void wide_to_ascii(char* const buffer, const wchar_t* const wide_char);
}