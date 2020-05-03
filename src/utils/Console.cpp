#include "Console.h"

#include <iostream>

namespace Console
{
	void print(const std::string &text)
	{
		std::cout << text;
	}

	char prompt(char validInputs[])
	{
		std::string input;
		//std::getline(std::cin, input);
		bool found = false;
        while(!found) {
            std::getline(std::cin, input);
            int len = sizeof(char*)/sizeof(validInputs[0]);
            for (int i = 0; i < len; i++) {
            	if (input[0] == validInputs[i]) {
            		found = true;
            		break;
            	}
            }
        }
        return input[0];
	}

	std::string prompt()
	{
		std::string input;
    	std::getline(std::cin, input);
    	return input;
	}
};