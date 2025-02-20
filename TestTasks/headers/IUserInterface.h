#pragma once

#include <iostream>
#include <map>
#include <string>
#include "Student.h"


class IUserInterface
{
public:
    virtual void ShowMenu(const std::map<int, std::string>& menuItems) = 0;
    virtual void ShowMessage(const std::string& message) = 0;
    virtual int GetUserChoice() = 0;
    virtual std::string GetUserInput(const std::string& prompt) = 0;

    virtual ~IUserInterface() = default;
};