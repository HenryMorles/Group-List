#include "../headers/GroupUI.h"
#include <iostream>

void GroupUI::Run() {
    Group group({}, 101);

    while (true) {
        ShowMenu();
        int choice;
        std::cout << "Select an action: ";
        std::cin >> choice;

        switch (choice) {
        case 1: AddStudent(group); break;
        case 2: EditStudent(group); break;
        case 3: DeleteStudent(group); break;
        case 4: FindStudent(group); break;
        case 5: ShowStudents(group); break;
        case 0: return;
        default: std::cout << "Invalid selection, please try again.\n";
        }
    }
}

void GroupUI::ShowMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add a student\n";
    std::cout << "2. Edit a student\n";
    std::cout << "3. Delete a student\n";
    std::cout << "4. Find a student\n";
    std::cout << "5. Show all students\n";
    std::cout << "0. Exit\n";
}

void GroupUI::AddStudent(Group& group) {
    int recBookNumber;
    std::string firstName, lastName;
    int specialization;

    std::cout << "Enter student record book number: ";
    std::cin >> recBookNumber;
    std::cout << "Enter first name: ";
    std::cin >> firstName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;
    std::cout << "Select specialization (0 - MATHEMATICS, 1 - PHYSICS, 2 - ECONOMICS, 3 - COMPUTER_SCIENCE): ";
    std::cin >> specialization;

    group.Add(Student(firstName, lastName, static_cast<Specialization>(specialization), recBookNumber));
    std::cout << "Student added successfully!\n";
}

void GroupUI::EditStudent(Group& group) {
    int recBookNumber, choice;
    std::cout << "Enter student record book number: ";
    std::cin >> recBookNumber;

    std::cout << "What would you like to edit?\n";
    std::cout << "1. First name\n2. Last name\n3. Specialization\n";
    std::cin >> choice;

    if (choice == 1) {
        std::string newFirstName;
        std::cout << "Enter new first name: ";
        std::cin >> newFirstName;
        group.EditFirstName(recBookNumber, newFirstName);
    }
    else if (choice == 2) {
        std::string newLastName;
        std::cout << "Enter new last name: ";
        std::cin >> newLastName;
        group.EditLastName(recBookNumber, newLastName);
    }
    else if (choice == 3) {
        int specialization;
        std::cout << "Select new specialization (0 - MATHEMATICS, 1 - PHYSICS, 2 - ECONOMICS, 3 - COMPUTER_SCIENCE): ";
        std::cin >> specialization;
        group.EditSpecialization(recBookNumber, static_cast<Specialization>(specialization));
    }
    else {
        std::cout << "Invalid selection.\n";
    }
}

void GroupUI::DeleteStudent(Group& group) {
    int recBookNumber;
    std::cout << "Enter student record book number to delete: ";
    std::cin >> recBookNumber;

    try {
        group.Delete(recBookNumber);
        std::cout << "Student deleted successfully!\n";
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void GroupUI::FindStudent(Group& group) {
    std::string firstName, lastName;
    std::cout << "Enter first name: ";
    std::cin >> firstName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;

    try {
        const Student& student = group.Find(firstName, lastName);
        std::cout << "Student found: " << student.getFirstName() << " " << student.getLastName() << " ("
            << student.getRecBookNumber() << ")\n";
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void GroupUI::ShowStudents(const Group& group) {
    std::cout << "\nList of students:\n";

    size_t studentCount = group.GetStudentCount();

    if (studentCount == 0) {
        std::cout << "No students in the group.\n";
        return;
    }

    const auto& students = group.GetStudents();

    for (const auto& student : students) {
        std::cout << "Record book number: " << student.getRecBookNumber()
            << ", First name: " << student.getFirstName()
            << ", Last name: " << student.getLastName()
            << ", Specialization: " << student.getSpecialization()
            << std::endl;
    }
}
