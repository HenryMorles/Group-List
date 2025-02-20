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
    std::cin >> choice;
    return choice;
}

std::string ConsoleUI::GetUserInput(const std::string& prompt)
{
    std::cout << prompt;
    std::cin.ignore();
    std::string input;
    std::getline(std::cin, input);
    return input;
}
