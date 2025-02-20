#include "../headers/Student.h"

Student::Student(const std::string& firstName, const std::string& lastName, Specialization specialization, int recBookNumber) : _firstName(firstName), _lastName(lastName), _specialization(specialization), _recBookNumber(recBookNumber)
{

}

const std::string& Student::GetFirstName() const
{
    return _firstName;
}

const std::string& Student::GetLastName() const
{
    return _lastName;
}

Specialization Student::GetSpecialization() const
{
    return _specialization;
}

int Student::GetRecBookNumber() const
{
    return _recBookNumber;
}

void Student::SetFirstName(const std::string& newFirstName)
{
    _firstName = newFirstName;
}

void Student::SetLastName(const std::string& newLastName)
{
    _lastName = newLastName;
}

void Student::SetSpecialization(const Specialization newSpecialization)
{
    _specialization = newSpecialization;
}
