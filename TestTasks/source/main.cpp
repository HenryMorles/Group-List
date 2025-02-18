#include "../headers/MenuManager.h"
#include "../headers/ConsoleUI.h"
#include "../headers/MenuActions.h"


int main()
{
    ConsoleUI userInterface;
    auto mainMenu = std::make_shared<MenuManager>(userInterface, "Main Menu");
  


    mainMenu->run();

    return 0;
}
