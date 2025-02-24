#include "../headers/MenuManager.h"
#include "../headers/ConsoleUI.h"
#include "../headers/MenuAction.h"
#include "../headers/Deanery.h"
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

    Deanery deanery(std::vector<std::shared_ptr<Group>>{});
    std::shared_ptr<Group> selectedGroup = nullptr;

    mainMenu->AddMenuItem(1, "Group Management", [&]() { SafeExecute([&]() { groupMenu->Run(); }, ui); });
    mainMenu->AddMenuItem(0, "Exit", []() {});

    groupMenu->AddMenuItem(1, "Create Group", [&]() { SafeExecute([&]() { MenuAction::CreateGroup(deanery, ui); }, ui); });
    groupMenu->AddMenuItem(2, "Delete Group", [&]() { SafeExecute([&]() { MenuAction::DeleteGroup(deanery, ui); }, ui); });
    groupMenu->AddMenuItem(3, "Select Group", [&]()
        {
            SafeExecute([&]()
                {
                    selectedGroup = MenuAction::SelectGroup(deanery, ui);
                    if (selectedGroup) studentMenu->Run();
                }, ui);
        });
    groupMenu->AddMenuItem(0, "Back", []() {});

    studentMenu->AddMenuItem(1, "Add Student", [&]() { SafeExecute([&]() { MenuAction::AddStudentToGroup(deanery, selectedGroup, ui); }, ui); });
    studentMenu->AddMenuItem(2, "Remove Student", [&]() { SafeExecute([&]() { MenuAction::RemoveStudentFromGroup(selectedGroup, ui); }, ui); });
    studentMenu->AddMenuItem(3, "List Students", [&]() { SafeExecute([&]() { MenuAction::ListStudentsInGroup(selectedGroup, ui); }, ui); });
    studentMenu->AddMenuItem(4, "Edit Student", [&]() { SafeExecute([&]() { editStudentMenu->Run(); }, ui); });
    studentMenu->AddMenuItem(0, "Back", []() {});

    editStudentMenu->AddMenuItem(1, "Edit First Name", [&]() { SafeExecute([&]() { MenuAction::EditStudentFirstName(selectedGroup, ui); }, ui); });
    editStudentMenu->AddMenuItem(2, "Edit Last Name", [&]() { SafeExecute([&]() { MenuAction::EditStudentLastName(selectedGroup, ui); }, ui); });
    editStudentMenu->AddMenuItem(3, "Edit Specialization", [&]() { SafeExecute([&]() { MenuAction::EditStudentSpecialization(selectedGroup, ui); }, ui); });
    editStudentMenu->AddMenuItem(0, "Back", []() {});

    SafeExecute([&]() { mainMenu->Run(); }, ui);

    return 0;
}