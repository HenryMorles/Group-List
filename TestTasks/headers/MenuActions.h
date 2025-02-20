#pragma once

#include "IUserInterface.h"
#include "Group.h"
#include <vector>
#include <memory>


namespace MenuActions
{
    void CreateGroup(std::vector<std::shared_ptr<Group>>& groups, IUserInterface& ui);
    void DeleteGroup(std::vector<std::shared_ptr<Group>>& groups, IUserInterface& ui);
    std::shared_ptr<Group> SelectGroup(std::vector<std::shared_ptr<Group>>& groups, IUserInterface& ui);

    void AddStudentToGroup(std::shared_ptr<Group> group, IUserInterface& ui, std::vector<std::shared_ptr<Group>>& groups);
    void RemoveStudentFromGroup(std::shared_ptr<Group> group, IUserInterface& ui);
    void ListStudentsInGroup(std::shared_ptr<Group> group, IUserInterface& ui);

    void EditStudentFirstName(std::shared_ptr<Group> group, IUserInterface& ui);
    void EditStudentLastName(std::shared_ptr<Group> group, IUserInterface& ui);
    void EditStudentSpecialization(std::shared_ptr<Group> group, IUserInterface& ui);
}