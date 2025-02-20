#pragma once

#include <string>

enum Specialization
{
    NONE,
    MATHEMATICS,
    PHYSICS,
    ECONOMICS,
    COMPUTER_SCIENCE
};

class Student
{
private:

    std::string _firstName;
    std::string _lastName;
    Specialization _specialization;
    int _recBookNumber;

public:

    Student(const std::string& firstName, const std::string& lastName, const Specialization specialization, const int recBookNumber);

    const std::string& GetFirstName() const;
    const std::string& GetLastName() const;
    Specialization GetSpecialization() const;
    int GetRecBookNumber() const;

    void SetFirstName(const std::string& newFirstName);
    void SetLastName(const std::string& newLastName);
    void SetSpecialization(const Specialization newSpecialization);
};

