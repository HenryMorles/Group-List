#pragma once


#include "IUserInterface.h"

class ConsoleUI : public IUserInterface
{
public:

    void ShowMenu(const std::map<int, std::string>& menuItems) override;
    void ShowMessage(const std::string& message) override;
    int GetUserChoice() override;
    std::string GetUserInput(const std::string& prompt) override;
};