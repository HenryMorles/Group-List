#include "../headers/ConsoleUI.h"

void ConsoleUI::ShowMenu(const std::map<int, std::string>& menuItems)
{
    for (const auto& item : menuItems)
    {
        std::cout << item.first << ") " << item.second << '\n';
    }
    std::cout << "0) Back\n";
    std::cout << "Select an option: ";
}

void ConsoleUI::ShowMessage(const std::string& message)
{
    std::cout << message << std::endl;
}

int ConsoleUI::GetUserChoice()
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

std::string ConsoleUI::GetUserInput(const std::string& prompt)
{
    std::cout << prompt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string input;
    std::getline(std::cin, input);
    return input;
}
