#include "../headers/IUserInterface.h"

bool IUserInterface::IsValidStringInput(std::string& input)
{
	bool validInput = !input.empty();
	for (char ch : input)
	{
		if (!std::isalpha(ch))
		{
			validInput = false;
			break;
		}
	}

	return validInput;
}
