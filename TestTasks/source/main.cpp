#include "../headers/MenuManager.h"
#include "../headers/ConsoleUI.h"
#include "../headers/MenuActions.h"
#include <vector>
#include <memory>

void SafeExecute(std::function<void()> action, IUserInterface& ui)
{
    try
    {
        action();
    }
    catch (const std::runtime_error& e)
    {
        ui.ShowMessage("Error: " + std::string(e.what()));
    }
}

int main()
{
    ConsoleUI ui;
    auto mainMenu = std::make_shared<MenuManager>(ui, "Main Menu");
    auto groupMenu = std::make_shared<MenuManager>(ui, "Group Management");
    auto studentMenu = std::make_shared<MenuManager>(ui, "Student Management");
    auto editStudentMenu = std::make_shared<MenuManager>(ui, "Edit Student");

    std::vector<std::shared_ptr<Group>> groups;
    std::shared_ptr<Group> selectedGroup = nullptr;

    mainMenu->AddMenuItem(1, "Group Management", [&]() { SafeExecute([&]() { groupMenu->Run(); }, ui); });

    groupMenu->AddMenuItem(1, "Create Group", [&]() { SafeExecute([&]() { MenuActions::CreateGroup(groups, ui); }, ui); });
    groupMenu->AddMenuItem(2, "Delete Group", [&]() { SafeExecute([&]() { MenuActions::DeleteGroup(groups, ui); }, ui); });
    groupMenu->AddMenuItem(3, "Select Group", [&]()
        {
            SafeExecute([&]()
                {
                    selectedGroup = MenuActions::SelectGroup(groups, ui);
                    if (selectedGroup) studentMenu->Run();
                }, ui);
        });
    studentMenu->AddMenuItem(1, "Add Student", [&]() { SafeExecute([&]() { MenuActions::AddStudentToGroup(selectedGroup, ui, groups); }, ui); });
    studentMenu->AddMenuItem(2, "Remove Student", [&]() { SafeExecute([&]() { MenuActions::RemoveStudentFromGroup(selectedGroup, ui); }, ui); });
    studentMenu->AddMenuItem(3, "List Students", [&]() { SafeExecute([&]() { MenuActions::ListStudentsInGroup(selectedGroup, ui); }, ui); });

    studentMenu->AddMenuItem(4, "Edit Student", [&]() { SafeExecute([&]() { editStudentMenu->Run(); }, ui); });

    editStudentMenu->AddMenuItem(1, "Edit First Name", [&]() { SafeExecute([&]() { MenuActions::EditStudentFirstName(selectedGroup, ui); }, ui); });
    editStudentMenu->AddMenuItem(2, "Edit Last Name", [&]() { SafeExecute([&]() { MenuActions::EditStudentLastName(selectedGroup, ui); }, ui); });
    editStudentMenu->AddMenuItem(3, "Edit Specialization", [&]() { SafeExecute([&]() { MenuActions::EditStudentSpecialization(selectedGroup, ui); }, ui); });

    SafeExecute([&]() { mainMenu->Run(); }, ui);

    return 0;
}