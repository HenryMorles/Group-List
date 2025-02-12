#pragma once

#include "Student.h"
#include "vector"
#include "memory"


class Group
{
private:

	std::vector<Student> _students;
	int _groupNumber;

	Student* FindStudentByRecBookNumber(int recBookNumber);
	const Student* FindStudentByRecBookNumber(int recBookNumber) const;

public:

	Group(std::vector<Student> students, int groupNumber);

	void Add(const Student& student);

	void EditFirstName(const int recBookNumber, const std::string& newFirstName);
	void EditLastName(const int recBookNumber, const std::string& newLastName);
	void EditSpecialization(const int recBookNumber, const Specialization newSpecialization);

	const std::vector<Student>& GetStudents() const;
	int GetGroupNumber() const;
	size_t GetStudentCount() const;

	std::unique_ptr<Student> Delete(const int recBookNumber);
	const Student& Find(const std::string& firstName, const std::string& lastName) const;

	Student& operator[] (int recBookNumber);
	const Student& operator[] (int recBookNumber) const;
};

