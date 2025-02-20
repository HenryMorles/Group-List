#pragma once

#include "IUserInterface.h"
#include <functional>
#include <memory>
#include <map>

class MenuManager
{
private:

    IUserInterface& _userInterface;
    std::map<int, std::function<void()>> _actions;
    std::map<int, std::shared_ptr<MenuManager>> _submenus;
    std::map<int, std::string> _descriptions;
    std::string _title;

public:

    MenuManager(IUserInterface& userInterface, const std::string& menuTitle);

    void AddMenuItem(int option, const std::string& description, std::function<void()> action);
    void AddSubMenu(int option, const std::string& description, std::shared_ptr<MenuManager> submenu);
    void Run();
};