#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "IUserInterface.h"

class ConsoleUI : public IUserInterface
{
public:

    void ShowMenu(const std::unordered_map<int, std::string>& menuItems) override;
    void ShowMessage(const std::string& message) override;
    int EnterMenuOptionChoice() override;
    int EnterValidInt(const std::string& prompt) override;
    std::string EnterValidString(const std::string& prompt) override;
};

#endif // CONSOLE_UI_H