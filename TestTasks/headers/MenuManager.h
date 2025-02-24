#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "IUserInterface.h"
#include <functional>
#include <memory>
#include <unordered_map>

class MenuManager
{
private:

    IUserInterface& _userInterface;
    std::unordered_map<int, std::function<void()>> _actions;
    std::unordered_map<int, std::shared_ptr<MenuManager>> _submenus;
    std::unordered_map<int, std::string> _descriptions;
    std::string _title;

public:

    MenuManager(IUserInterface& userInterface, const std::string& menuTitle);

    void AddMenuItem(int option, const std::string& description, 
        std::function<void()> action);

    void AddSubMenu(int option, const std::string& description, 
        std::shared_ptr<MenuManager> submenu);
    void Run();
};

#endif // MENU_MANAGER_H