#include "../headers/Student.h"

Student::Student(const std::string& firstName, const std::string& lastName, 
    Specialization specialization, int recBookNumber, int groupNumber)
    : _firstName(firstName), _lastName(lastName), _specialization(specialization),
    _recBookNumber(recBookNumber), _groupNumber(groupNumber)
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

int Student::GetGroupNumber() const
{
    return _groupNumber;
}

void Student::SetFirstName(const std::string& newFirstName)
{
    _firstName = newFirstName;
}

void Student::SetLastName(const std::string& newLastName)
{
    _lastName = newLastName;
}

void Student::SetSpecialization(Specialization newSpecialization)
{
    _specialization = newSpecialization;
}

void Student::GetGroupNumber(int newGroupNumber)
{
    _groupNumber = newGroupNumber;
}