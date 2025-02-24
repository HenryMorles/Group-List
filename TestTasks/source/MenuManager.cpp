#include "../headers/MenuManager.h"

MenuManager::MenuManager(IUserInterface& userInterface, const std::string& menuTitle)
    : _userInterface(userInterface), _title(menuTitle)
{

}

void MenuManager::AddMenuItem(
    int option, const std::string& description, std::function<void()> action)
{
    _actions[option] = action;
    _descriptions[option] = description;
}

void MenuManager::AddSubMenu(
    int option, const std::string& description, std::shared_ptr<MenuManager> submenu)
{
    _submenus[option] = submenu;
    _descriptions[option] = description;
}

void MenuManager::Run()
{
    int choice;
    bool validChoice;

    do
    {
        std::unordered_map<int, std::string> menuItems;
        for (const auto& item : _descriptions)
        {
            menuItems[item.first] = item.second;
        }

        _userInterface.ShowMessage("\n==== " + _title + " ====\n");
        _userInterface.ShowMenu(menuItems);
        _userInterface.ShowMessage("Select an option: ");

        do
        {
            choice = _userInterface.EnterMenuOptionChoice();
            validChoice = 
                (_descriptions.find(choice) != _descriptions.end() || choice == 0);

            if (!validChoice)
            {
                _userInterface.ShowMessage(
                    "Invalid choice. Please select a valid option.");
            }
        } while (!validChoice);

        if (choice == 0)
        {
            _userInterface.ShowMessage("Returning...");
        }
        else if (_actions.find(choice) != _actions.end())
        {
            _actions[choice]();
        }
        else if (_submenus.find(choice) != _submenus.end())
        {
            _submenus[choice]->Run();
        }

    } while (choice != 0);
}