#pragma once

#include <string>

namespace Console
{
	void print(const std::string &text);
	char prompt(char validInputs[]);
	std::string prompt();
};