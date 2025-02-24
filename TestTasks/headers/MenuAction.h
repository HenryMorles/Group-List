#ifndef MENU_ACTION_H
#define MENU_ACTION_H

#include "IUserInterface.h"
#include "Deanery.h"
#include "Group.h"
#include <vector>
#include <memory>


namespace MenuAction
{
    using GroupPtr = std::shared_ptr<Group>;

    void CreateGroup(Deanery& deanery, IUserInterface& ui);
    void DeleteGroup(Deanery& deanery, IUserInterface& ui);
    GroupPtr SelectGroup(Deanery& deanery, IUserInterface& ui);

    void AddStudentToGroup(Deanery& deanery, GroupPtr group, IUserInterface& ui);
    void RemoveStudentFromGroup(GroupPtr group, IUserInterface& ui);
    void ListStudentsInGroup(GroupPtr group, IUserInterface& ui);

    void EditStudentFirstName(GroupPtr group, IUserInterface& ui);
    void EditStudentLastName(GroupPtr group, IUserInterface& ui);
    void EditStudentSpecialization(GroupPtr group, IUserInterface& ui);
}

#endif // MENU_ACTION_H