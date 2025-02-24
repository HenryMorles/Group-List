#include "../headers/MenuAction.h"
#include "../headers/Student.h"
#include <iostream>
#include <cctype>

namespace MenuAction
{
    std::string ConvertSpecializationToString(Specialization spec)
    {
        switch (spec)
        {
        case MATHEMATICS: return std::string("Mathematics");
        case PHYSICS: return std::string("Physics");
        case ECONOMICS: return std::string("Economics");
        case COMPUTER_SCIENCE: return std::string("Computer Science");
        default: return std::string("None");
        }
    }

    Specialization ChooseSpecialization(IUserInterface& ui)
    {
        int choice;
        bool validInput;
        
        ui.ShowMessage("Choose specialization:");

        std::unordered_map<int, std::string> specializationOptions;
        specializationOptions[1] = "Mathematics";
        specializationOptions[2] = "Physics";
        specializationOptions[3] = "Economics";
        specializationOptions[4] = "Computer Science";
        specializationOptions[0] = "None";

        ui.ShowMenu(specializationOptions);

        do
        {
            choice = ui.EnterValidInt("Enter choice: ");

            const int specilizationCount = 4;
            validInput = choice >= 0 && choice <= specilizationCount;

            if (!validInput)
            {
                ui.ShowMessage(
                    "Invalid choice. Please enter a number between 0 and : " 
                    + std::to_string(specilizationCount));
            }
        } while (!validInput);

        return static_cast<Specialization>(choice);
    }

    void CreateGroup(Deanery& deanery, IUserInterface& ui)
    {
        int groupNumber = ui.EnterValidInt("Enter new group number: ");

        auto newGroup = std::make_shared<Group>(std::vector<Student>{}, groupNumber);
        deanery.AddGroup(newGroup);

        ui.ShowMessage("Group " + std::to_string(groupNumber) + " created successfully!");
    }

    void DeleteGroup(Deanery& deanery, IUserInterface& ui)
    {
        if (deanery.IsGroupListEmpty())
        {
            ui.ShowMessage("No groups available to delete.");
            return;
        }

        ui.ShowMessage("Available groups:");
        for (int i = 0; i < deanery.GetGroupCount(); ++i)
        {
            ui.ShowMessage(std::to_string(i + 1) + ") Group " + 
                std::to_string(deanery.GetGroupByIndex(i)->GetGroupNumber()));
        }

        int choice;
        do
        {
            choice = ui.EnterValidInt("Select a group to delete (0 to cancel): ");
            if (choice < 0 || choice > static_cast<int>(deanery.GetGroupCount()))
            {
                ui.ShowMessage("Invalid selection. Try again.");
            }
        } while (choice < 0 || choice > static_cast<int>(deanery.GetGroupCount()));

        if (choice > 0)
        {
            deanery.DeleteGroupByIndex(choice - 1);
            ui.ShowMessage("Group deleted successfully!");
        }
    }

    GroupPtr SelectGroup(Deanery& deanery, IUserInterface& ui)
    {
        if (deanery.IsGroupListEmpty())
        {
            ui.ShowMessage("No groups available. Please create a group first.");
            return nullptr;
        }

        ui.ShowMessage("Available groups:");
        for (int i = 0; i < deanery.GetGroupCount(); ++i)
        {
            ui.ShowMessage( std::to_string(i + 1) + ") Group " + 
                std::to_string(deanery.GetGroupByIndex(i)->GetGroupNumber()));
        }

        int choice;
        do
        {
            choice = ui.EnterValidInt("Select a group (0 to cancel): ");
            if (choice < 0 || choice > static_cast<int>(deanery.GetGroupCount()))
            {
                ui.ShowMessage("Invalid selection. Try again.");
            }
        } while (choice < 0 || choice > static_cast<int>(deanery.GetGroupCount()));

        return (choice > 0) ? deanery.GetGroupByIndex(choice - 1) : nullptr;
    }

    void AddStudentToGroup(Deanery& deanery, GroupPtr group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        std::string firstName = ui.EnterValidString("Enter student first name: ");
        std::string lastName = ui.EnterValidString("Enter student last name: ");

        int recBookNumber = ui.EnterValidInt("Enter student record book number: ");
        Specialization spec = ChooseSpecialization(ui);

        Student* checkStudent = deanery.FindStudentFromAllGroups(recBookNumber);

        if (!checkStudent)
        {
            Student newStudent(firstName, lastName, spec, recBookNumber, group->GetGroupNumber());
            group->Add(newStudent);
            ui.ShowMessage("Student added successfully!");
        }
        else
        {
            ui.ShowMessage(
                "Error: Student with such record book number already exists in group " 
                + std::to_string(checkStudent->GetGroupNumber()));
        }
    }

    void RemoveStudentFromGroup(GroupPtr group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        int recBookNumber = ui.EnterValidInt(
            "Enter student record book number to remove: ");

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

    void ListStudentsInGroup(GroupPtr group, IUserInterface& ui)
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
            ui.ShowMessage("\nStudents in Group " + 
                std::to_string(group->GetGroupNumber()) + ":");

            for (const auto& student : students)
            {
                ui.ShowMessage(student.GetFirstName() + " " + student.GetLastName()
                    + " (Record Book #: " 
                    + std::to_string(student.GetRecBookNumber()) + ")"
                    + " - Specialization: " 
                    + ConvertSpecializationToString(student.GetSpecialization()));
            }
        }
    }

    void EditStudentFirstName(GroupPtr group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        int recBookNumber = ui.EnterValidInt(
            "Enter student record book number to edit first name: ");
        std::string newFirstName = ui.EnterValidString(
            "Enter new first name: ");

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

    void EditStudentLastName(GroupPtr group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        int recBookNumber = ui.EnterValidInt(
            "Enter student record book number to edit last name: ");
        std::string newLastName = ui.EnterValidString("Enter new last name: ");

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

    void EditStudentSpecialization(GroupPtr group, IUserInterface& ui)
    {
        if (!group)
        {
            throw std::runtime_error("No group selected.");
        }

        int recBookNumber = ui.EnterValidInt(
            "Enter student record book number to edit specialization: ");

        Specialization newSpec = ChooseSpecialization(ui);

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