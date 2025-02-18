#pragma once

#include <iostream>
#include <map>
#include <string>


class UserInterface
{
public:
    virtual void showMenu(const std::map<int, std::string>& menuItems) = 0;
    virtual void showMessage(const std::string& message) = 0;
    virtual int getUserChoice() = 0;
    virtual std::string getUserInput(const std::string& prompt) = 0;
    virtual ~UserInterface() = default;
};