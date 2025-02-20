#include "../headers/MenuActions.h"
#include "../headers/Student.h"
#include <iostream>
#include <cctype>

namespace MenuActions
{
    std::string GetValidStringInput(const std::string& prompt)
    {
        std::string value;
        bool validInput;

        do
        {
            std::cout << prompt;
            std::cin >> value;

            validInput = !value.empty();
            for (char ch : value)
            {
                if (!std::isalpha(ch))
                {
                    validInput = false;
                    break;
                }
            }

            if (!validInput)
            {
                std::cout << "Invalid input. Please enter a name with letters only.\n";
            }

        } while (!validInput);

        return value;
    }

    int GetValidIntInput(const std::string& prompt)
    {
        int value;
        bool validInput;

        do
        {
            std::cout << prompt;
            std::cin >> value;
            validInput = !std::cin.fail();

            if (!validInput)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (!validInput);

        return value;
    }

    std::string SpecializationToString(Specialization spec)
    {
        switch (spec)
        {
        case MATHEMATICS: return "Mathematics"; break;
        case PHYSICS: return "Physics"; break;
        case ECONOMICS: return "Economics"; break;
        case COMPUTER_SCIENCE: return "Computer Science"; break;
        default: return "None"; break;
        }
    }

    Specialization ChooseSpecialization()
    {
        int choice;
        bool validInput;

        std::cout << "Choose specialization:\n";
        std::cout << "1) Mathematics\n";
        std::cout << "2) Physics\n";
        std::cout << "3) Economics\n";
        std::cout << "4) Computer Science\n";
        std::cout << "0) None\n";

        do
        {
            std::cout << "Enter choice: ";
            std::cin >> choice;
            validInput = !std::cin.fail() && choice >= 0 && choice <= 4;

            if (!validInput)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Please enter a number between 0 and 4: ";
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (!validInput);

        switch (choice)
        {
        case 1: return MATHEMATICS; break;
        case 2: return PHYSICS; break;
        case 3: return ECONOMICS; break;
        case 4: return COMPUTER_SCIENCE; break;
        default: return NONE; break;
        }
    }

    void CreateGroup(std::vector<std::shared_ptr<Group>>& groups, IUserInterface& ui)
    {
        int groupNumber = GetValidIntInput("Enter new group number: ");

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

        int choice;
        do
        {
            choice = GetValidIntInput("Select a group to delete (0 to cancel): ");
            if (choice < 0 || choice > static_cast<int>(groups.size()))
            {
                std::cout << "Invalid selection. Try again.\n";
            }
        } while (choice < 0 || choice > static_cast<int>(groups.size()));

        if (choice > 0)
        {
            groups.erase(groups.begin() + (choice - 1));
            ui.ShowMessage("Group deleted successfully!");
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

        int choice;
        do
        {
            choice = GetValidIntInput("Select a group (0 to cancel): ");
            if (choice < 0 || choice > static_cast<int>(groups.size()))
            {
                std::cout << "Invalid selection. Try again.\n";
            }
        } while (choice < 0 || choice > static_cast<int>(groups.size()));

        return (choice > 0) ? groups[choice - 1] : nullptr;
    }

    void AddStudentToGroup(std::shared_ptr<Group> group, IUserInterface& ui, std::vector<std::shared_ptr<Group>>& groups)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        std::string firstName = GetValidStringInput("Enter student first name: ");
        std::string lastName = GetValidStringInput("Enter student last name: ");

        int recBookNumber = GetValidIntInput("Enter student record book number: ");
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
            ui.ShowMessage("Error: Student with such record book number already exists in group " +
                std::to_string(foundGroup->GetGroupNumber()));
        }
    }

    void RemoveStudentFromGroup(std::shared_ptr<Group> group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        int recBookNumber = GetValidIntInput("Enter student record book number to remove: ");

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

        int recBookNumber = GetValidIntInput("Enter student record book number to edit first name: ");
        std::string newFirstName = GetValidStringInput("Enter new first name: ");

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

        int recBookNumber = GetValidIntInput("Enter student record book number to edit last name: ");
        std::string newLastName = GetValidStringInput("Enter new last name: ");

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

        int recBookNumber = GetValidIntInput("Enter student record book number to edit specialization: ");
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