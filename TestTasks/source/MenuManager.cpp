#include "../headers/MenuManager.h"

MenuManager::MenuManager(UserInterface& userInterface, const std::string& menuTitle) : userInterface(userInterface), title(menuTitle) 
{

}

void MenuManager::addMenuItem(int option, const std::string& description, std::function<void()> action)
{
    actions[option] = action;
    descriptions[option] = description;
}

void MenuManager::addSubMenu(int option, const std::string& description, std::shared_ptr<MenuManager> submenu)
{
    submenus[option] = submenu;
    descriptions[option] = description;
}

void MenuManager::run()
{
    int choice;

    do
    {
        std::map<int, std::string> menuItems;
        for (const auto& item : descriptions)
        {
            menuItems[item.first] = item.second;
        }

        userInterface.showMessage("\n==== " + title + " ====\n");
        userInterface.showMenu(menuItems);
        choice = userInterface.getUserChoice();

        if (choice == 0)
        {
            userInterface.showMessage("Returning...");
        }
        else if (actions.find(choice) != actions.end())
        {
            actions[choice]();
        }
        else if (submenus.find(choice) != submenus.end())
        {
            submenus[choice]->run();
        }
        else
        {
            userInterface.showMessage("Invalid choice. Try again.");
        }

    } while (choice != 0);
}