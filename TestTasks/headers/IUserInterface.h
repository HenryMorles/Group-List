#ifndef IUSER_INTERFACE_H
#define IUSER_INTERFACE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include "Student.h"


class IUserInterface
{
protected:
    virtual bool IsValidStringInput(std::string& input);

public:
    virtual void ShowMenu(const std::unordered_map<int, std::string>& menuItems) = 0;
    virtual void ShowMessage(const std::string& message) = 0;

    virtual int EnterMenuOptionChoice() = 0;
    virtual int EnterValidInt(const std::string& prompt) = 0;
    virtual std::string EnterValidString(const std::string& prompt) = 0;

    virtual ~IUserInterface() = default;
};

#endif // IUSER_INTERFACE_H