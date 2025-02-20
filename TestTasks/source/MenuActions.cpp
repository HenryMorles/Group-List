#include "../headers/MenuActions.h"
#include "../headers/Student.h"
#include <iostream>

namespace MenuActions
{
    std::string SpecializationToString(Specialization spec)
    {
        switch (spec)
        {
        case MATHEMATICS: return "Mathematics";
        case PHYSICS: return "Physics";
        case ECONOMICS: return "Economics";
        case COMPUTER_SCIENCE: return "Computer Science";
        default: return "None";
        }
    }

    Specialization ChooseSpecialization()
    {
        std::cout << "Choose specialization:\n";
        std::cout << "1) Mathematics\n";
        std::cout << "2) Physics\n";
        std::cout << "3) Economics\n";
        std::cout << "4) Computer Science\n";
        std::cout << "0) None\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1: return MATHEMATICS;
        case 2: return PHYSICS;
        case 3: return ECONOMICS;
        case 4: return COMPUTER_SCIENCE;
        default: return NONE;
        }
    }

    void CreateGroup(std::vector<std::shared_ptr<Group>>& groups, IUserInterface& ui)
    {
        std::cout << "Enter new group number: ";
        int groupNumber;
        std::cin >> groupNumber;

        auto newGroup = std::make_shared<Group>(std::vector<Student>{}, groupNumber);
        groups.push_back(newGroup);

        ui.ShowMessage("Group " + std::to_string(groupNumber) + " created successfully!");
    }

    void DeleteGroup(std::vector<std::shared_ptr<Group>>& groups, IUserInterface& ui)
    {
        if (groups.empty())
        {
            ui.ShowMessage("No groups available to delete.");
            return;
        }

        std::cout << "Available groups:\n";
        for (size_t i = 0; i < groups.size(); ++i)
        {
            std::cout << i + 1 << ") Group " << groups[i]->GetGroupNumber() << "\n";
        }

        std::cout << "Select a group to delete (0 to cancel): ";
        int choice;
        std::cin >> choice;

        if (choice > 0 && choice <= static_cast<int>(groups.size()))
        {
            groups.erase(groups.begin() + (choice - 1));
            ui.ShowMessage("Group deleted successfully!");
        }
        else
        {
            ui.ShowMessage("Invalid selection.");
        }
    }

    std::shared_ptr<Group> SelectGroup(std::vector<std::shared_ptr<Group>>& groups, IUserInterface& ui)
    {
        if (groups.empty())
        {
            ui.ShowMessage("No groups available. Please create a group first.");
            return nullptr;
        }

        std::cout << "Available groups:\n";
        for (size_t i = 0; i < groups.size(); ++i)
        {
            std::cout << i + 1 << ") Group " << groups[i]->GetGroupNumber() << "\n";
        }

        std::cout << "Select a group (0 to cancel): ";
        int choice;
        std::cin >> choice;

        if (choice > 0 && choice <= static_cast<int>(groups.size()))
        {
            return groups[choice - 1];
        }

        ui.ShowMessage("Invalid selection.");
        return nullptr;
    }

    void MenuActions::AddStudentToGroup(std::shared_ptr<Group> group, IUserInterface& ui, std::vector<std::shared_ptr<Group>>& groups)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        std::cout << "Enter student first name: ";
        std::string firstName;
        std::cin >> firstName;
        std::cout << "Enter student last name: ";
        std::string lastName;
        std::cin >> lastName;
        std::cout << "Enter student record book number: ";
        int recBookNumber;
        std::cin >> recBookNumber;

        Specialization spec = ChooseSpecialization();

        auto [checkStudent, foundGroup] = Group::FindStudentFromAllGroups(groups, recBookNumber);

        if (!checkStudent)
        {
            Student newStudent(firstName, lastName, spec, recBookNumber);
            group->Add(newStudent);
            ui.ShowMessage("Student added successfully!");
        }
        else
        {
            ui.ShowMessage("Error: Student with such rec book number already exists in group " +
                std::to_string(foundGroup->GetGroupNumber()));
        }
    }

    void RemoveStudentFromGroup(std::shared_ptr<Group> group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        std::cout << "Enter student record book number to remove: ";
        int recBookNumber;
        std::cin >> recBookNumber;

        try
        {
            group->Delete(recBookNumber);
            ui.ShowMessage("Student removed successfully!");
        }
        catch (const std::runtime_error& e)
        {
            ui.ShowMessage(std::string("Error: ") + e.what());
        }
    }

    void ListStudentsInGroup(std::shared_ptr<Group> group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        const auto& students = group->GetStudents();
        if (students.empty())
        {
            ui.ShowMessage("No students in this group.");
        }
        else
        {
            std::cout << "\nStudents in Group " << group->GetGroupNumber() << ":\n";
            for (const auto& student : students)
            {
                std::cout << student.GetFirstName() << " " << student.GetLastName()
                    << " (Record Book #: " << student.GetRecBookNumber() << ")"
                    << " - Specialization: " << SpecializationToString(student.GetSpecialization()) << "\n";
            }
        }
    }

    void EditStudentFirstName(std::shared_ptr<Group> group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        std::cout << "Enter student record book number to edit first name: ";
        int recBookNumber;
        std::cin >> recBookNumber;

        std::cout << "Enter new first name: ";
        std::string newFirstName;
        std::cin >> newFirstName;

        try
        {
            group->EditFirstName(recBookNumber, newFirstName);
            ui.ShowMessage("Student first name updated successfully!");
        }
        catch (const std::runtime_error& e)
        {
            ui.ShowMessage(std::string("Error: ") + e.what());
        }
    }

    void EditStudentLastName(std::shared_ptr<Group> group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        std::cout << "Enter student record book number to edit last name: ";
        int recBookNumber;
        std::cin >> recBookNumber;

        std::cout << "Enter new last name: ";
        std::string newLastName;
        std::cin >> newLastName;

        try
        {
            group->EditLastName(recBookNumber, newLastName);
            ui.ShowMessage("Student last name updated successfully!");
        }
        catch (const std::runtime_error& e)
        {
            ui.ShowMessage(std::string("Error: ") + e.what());
        }
    }

    void EditStudentSpecialization(std::shared_ptr<Group> group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        std::cout << "Enter student record book number to edit specialization: ";
        int recBookNumber;
        std::cin >> recBookNumber;

        Specialization newSpec = ChooseSpecialization();

        try
        {
            group->EditSpecialization(recBookNumber, newSpec);
            ui.ShowMessage("Student specialization updated successfully!");
        }
        catch (const std::runtime_error& e)
        {
            ui.ShowMessage(std::string("Error: ") + e.what());
        }
    }
}