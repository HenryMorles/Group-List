#pragma once


#include "UserInterface.h"

class ConsoleUI : public UserInterface
{
public:

    void showMenu(const std::map<int, std::string>& menuItems) override;

    void showMessage(const std::string& message) override;

    int getUserChoice() override;

    std::string getUserInput(const std::string& prompt) override;
};