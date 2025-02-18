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

    Student(const std::string& firstName, const std::string& lastName, Specialization specialization, int recBookNumber);

    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    Specialization getSpecialization() const;
    int getRecBookNumber() const;

    void setFirstName(const std::string& newFirstName);
    void setLastName(const std::string& newLastName);
    void setSpecialization(Specialization newSpecialization);
};

