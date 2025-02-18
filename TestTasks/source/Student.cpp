#include "../headers/Student.h"

Student::Student(const std::string& firstName, const std::string& lastName, Specialization specialization, int recBookNumber) : _firstName(firstName), _lastName(lastName), _specialization(specialization), _recBookNumber(recBookNumber)
{

}

const std::string& Student::getFirstName() const
{
    return _firstName;
}

const std::string& Student::getLastName() const
{
    return _lastName;
}

Specialization Student::getSpecialization() const
{
    return _specialization;
}

int Student::getRecBookNumber() const
{
    return _recBookNumber;
}

void Student::setFirstName(const std::string& newFirstName)
{
    _firstName = newFirstName;
}

void Student::setLastName(const std::string& newLastName)
{
    _lastName = newLastName;
}

void Student::setSpecialization(Specialization newSpecialization)
{
    _specialization = newSpecialization;
}
