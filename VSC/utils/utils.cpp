#include "utils.hpp"

void rl::utils::wide_to_ascii(char* const buffer, const wchar_t* const wide_char)
{
	int i;

	for (i = 0; wide_char[i] >= 0x20 && wide_char[i] <= 0x7E; ++i)
		buffer[i] = static_cast<char>(wide_char[i]);

	buffer[i] = '\0';
}