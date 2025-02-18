#pragma once

#include "Group.h"

class GroupUI {
public:
    static void Run();
private:
    static void ShowMenu();
    static void AddStudent(Group& group);
    static void EditStudent(Group& group);
    static void DeleteStudent(Group& group);
    static void FindStudent(Group& group);
    static void ShowStudents(const Group& group);
};
