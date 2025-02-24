#ifndef DEANERY_H
#define DEANERY_H

#include <vector>
#include <memory>
#include "Group.h"

class Deanery
{
private:
    std::vector<std::shared_ptr<Group>> _groups;
    std::shared_ptr<Group> FindGroupByNumber(int groupNumber);
    std::shared_ptr<const Group> FindGroupByNumber(int groupNumber) const;

public:
    Deanery();
    Deanery(const std::vector<std::shared_ptr<Group>>& groups);

    void AddGroup(std::shared_ptr<Group> group);
    Student* FindStudentFromAllGroups(int recBookNumber);
    bool IsGroupListEmpty() const;
    int GetGroupCount() const;

    std::shared_ptr<Group> GetGroupByIndex(int index);
    void DeleteGroupByIndex(int index);

    std::shared_ptr<Group> operator[] (int groupNumber);
    std::shared_ptr<const Group> operator[] (int groupNumber) const;
};

#endif // DEANERY_H
