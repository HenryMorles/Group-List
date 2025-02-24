#ifndef STUDENT_H
#define STUDENT_H

#include "Specelization.h"
#include <string>

class Student
{
private:

    std::string _firstName;
    std::string _lastName;
    Specialization _specialization;
    int _recBookNumber;
    int _groupNumber;

public:

    Student(const std::string& firstName, const std::string& lastName,
        Specialization specialization, int recBookNumber, int groupNumber);

    const std::string& GetFirstName() const;
    const std::string& GetLastName() const;
    Specialization GetSpecialization() const;
    int GetRecBookNumber() const;
    int GetGroupNumber() const;

    void SetFirstName(const std::string& newFirstName);
    void SetLastName(const std::string& newLastName);
    void SetSpecialization(Specialization newSpecialization);
    void GetGroupNumber(int newGroupNumber);
};

#endif // STUDENT_H