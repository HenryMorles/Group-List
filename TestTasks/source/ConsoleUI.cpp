#include "../headers/ConsoleUI.h"

void ConsoleUI::showMenu(const std::map<int, std::string>& menuItems)
{
    for (const auto& item : menuItems)
    {
        std::cout << item.first << ") " << item.second << '\n';
    }
    std::cout << "0) Back\n";
    std::cout << "Select an option: ";
}

void ConsoleUI::showMessage(const std::string& message)
{
    std::cout << message << std::endl;
}

int ConsoleUI::getUserChoice()
{
    int choice;
    std::cin >> choice;
    return choice;
}

std::string ConsoleUI::getUserInput(const std::string& prompt)
{
    std::cout << prompt;
    std::string input;
    std::cin.ignore();
    std::getline(std::cin, input);
    return input;
}
