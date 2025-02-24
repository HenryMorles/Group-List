#include "../headers/ConsoleUI.h"

void ConsoleUI::ShowMenu(const std::unordered_map<int, std::string>& menuItems)
{
	for (const auto& item : menuItems)
	{
		std::cout << item.first << ") " << item.second << '\n';
	}
}

void ConsoleUI::ShowMessage(const std::string& message)
{
	std::cout << message << std::endl;
}

int ConsoleUI::EnterMenuOptionChoice()
{
	int choice;
	bool validInput;

	do
	{
		std::cin >> choice;
		validInput = !std::cin.fail();

		if (!validInput)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a number: ";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (!validInput);

	return choice;
}

int ConsoleUI::EnterValidInt(const std::string& prompt)
{
	int value;
	bool validInput;

	do
	{
		std::cout << prompt;
		std::cin >> value;
		validInput = !std::cin.fail();

		if (!validInput)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a number.\n";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (!validInput);

	return value;
}

std::string ConsoleUI::EnterValidString(const std::string& prompt)
{
	std::string value;
	bool validInput;

	do
	{
		std::cout << prompt;
		std::cin >> value;

		validInput = !value.empty();
		for (char ch : value)
		{
			if (!std::isalpha(ch))
			{
				validInput = false;
				break;
			}
		}

		if (!validInput)
		{
			std::cout << "Invalid input. Please enter a name with letters only.\n";
		}

	} while (!validInput);

	return value;
}