#pragma once

#include "UserInterface.h"
#include <functional>
#include <memory>
#include <map>

class MenuManager
{
private:

    UserInterface& userInterface;
    std::map<int, std::function<void()>> actions;
    std::map<int, std::shared_ptr<MenuManager>> submenus;
    std::map<int, std::string> descriptions;
    std::string title;

public:

    MenuManager(UserInterface& userInterface, const std::string& menuTitle);

    void addMenuItem(int option, const std::string& description, std::function<void()> action);

    void addSubMenu(int option, const std::string& description, std::shared_ptr<MenuManager> submenu);

    void run();
};