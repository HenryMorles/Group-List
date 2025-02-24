#include "../headers/Deanery.h"
#include <stdexcept>
#include <algorithm>


std::shared_ptr<Group> Deanery::FindGroupByNumber(int groupNumber)
{
    auto it = std::find_if(_groups.begin(), _groups.end(),
        [groupNumber](const std::shared_ptr<Group>& group)
        { return group->GetGroupNumber() == groupNumber; });

    return (it != _groups.end()) ? *it : nullptr;
}

std::shared_ptr<const Group> Deanery::FindGroupByNumber(int groupNumber) const
{
    auto it = std::find_if(_groups.begin(), _groups.end(),
        [groupNumber](const std::shared_ptr<Group>& group)
        { return group->GetGroupNumber() == groupNumber; });

    return (it != _groups.end()) ? *it : nullptr;
}

Deanery::Deanery() {}

Deanery::Deanery(const std::vector<std::shared_ptr<Group>>& groups) : _groups(groups) {}

void Deanery::AddGroup(std::shared_ptr<Group> group)
{
    for (const auto& existingGroup : _groups)
    {
        if (existingGroup->GetGroupNumber() == group->GetGroupNumber())
        {
            throw std::runtime_error("Group with this number already exists in the deanery.");
        }
    }

    _groups.push_back(group);
}

Student* Deanery::FindStudentFromAllGroups(int recBookNumber)
{
    for (auto& group : _groups)
    {
        Student* student = group->FindStudentByRecBookNumber(recBookNumber);
        if (student)
        {
            return student;
        }
    }
    return nullptr;
}

bool Deanery::IsGroupListEmpty() const
{
    return _groups.empty();
}

int Deanery::GetGroupCount() const
{
    return static_cast<int>(_groups.size());
}

std::shared_ptr<Group> Deanery::GetGroupByIndex(int index)
{
    if (index < 0 || index >= static_cast<int>(_groups.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    return _groups[index];
}

void Deanery::DeleteGroupByIndex(int index)
{
    if (index < 0 || index >= static_cast<int>(_groups.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    _groups.erase(_groups.begin() + index);
}

std::shared_ptr<Group> Deanery::operator[](int groupNumber)
{
    auto group = FindGroupByNumber(groupNumber);
    if (!group)
    {
        throw std::runtime_error("Group not found");
    }
    return group;
}

std::shared_ptr<const Group> Deanery::operator[](int groupNumber) const
{
    auto group = FindGroupByNumber(groupNumber);
    if (!group)
    {
        throw std::runtime_error("Group not found");
    }
    return group;
}
