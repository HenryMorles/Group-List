#include "Group.h"
#include <stdexcept>


Student* Group::FindStudentByRecBookNumber(int recBookNumber)
{
	auto it = std::find_if(_students.begin(), _students.end(),
		[recBookNumber](Student& student) { return student._recBookNumber == recBookNumber; });

	return (it != _students.end()) ? &(*it) : nullptr;
}

const Student* Group::FindStudentByRecBookNumber(int recBookNumber) const
{
	auto it = std::find_if(_students.begin(), _students.end(),
		[recBookNumber](const Student& student) { return student._recBookNumber == recBookNumber; });

	return (it != _students.end()) ? &(*it) : nullptr;
}

Group::Group(std::vector<Student> students, int groupNumber) : _students(std::move(students)), _groupNumber(groupNumber)
{

}

void Group::Add(const Student& student)
{
	_students.push_back(student);
}

void Group::EditFirstName(int recBookNumber, const std::string& newFirstName) 
{
	Student* student = FindStudentByRecBookNumber(recBookNumber);
	if (student) {
		student->_firstName = newFirstName;
	}
	else {
		throw std::runtime_error("Student is not found");
	}
}

void Group::EditLastName(const int recBookNumber, const std::string& newLastName)
{
	Student* student = FindStudentByRecBookNumber(recBookNumber);
	if (student) {
		student->_lastName = newLastName;
	}
	else {
		throw std::runtime_error("Student is not found");
	}
}

void Group::EditSpecialization(const int recBookNumber, const Specialization newSpecialization)
{
	Student* student = FindStudentByRecBookNumber(recBookNumber);
	if (student) {
		student->_specialization = newSpecialization;
	}
	else {
		throw std::runtime_error("Student is not found");
	}
}

const std::vector<Student>& Group::GetStudents() const 
{
	return _students;
}

int Group::GetGroupNumber() const
{
	return _groupNumber;
}

size_t Group::GetStudentCount() const
{
	return _students.size();
}

std::unique_ptr<Student> Group::Delete(int recBookNumber)
{
	Student* student = FindStudentByRecBookNumber(recBookNumber);

	if (student)
	{
		auto removedStudent = std::make_unique<Student>(std::move(*student));

		_students.erase(std::remove_if(_students.begin(), _students.end(),
			[recBookNumber](const Student& s) { return s._recBookNumber == recBookNumber; }), _students.end());

		return removedStudent;
	}

	throw std::runtime_error("Student is not found");
}

const Student& Group::Find(const std::string& firstName, const std::string& lastName) const
{
	auto it = std::find_if(_students.begin(), _students.end(),
		[&firstName, &lastName](const Student& student) {
			return student._firstName == firstName && student._lastName == lastName;
		});

	if (it != _students.end()) {
		return *it;
	}

	throw std::runtime_error("Student is not found");
}


Student& Group::operator[](int recBookNumber)
{
	Student* student = FindStudentByRecBookNumber(recBookNumber);

	if (student)
	{
		return *student;
	}

	throw std::runtime_error("Student is not found");
}

const Student& Group::operator[](int recBookNumber) const
{
	const Student* student = FindStudentByRecBookNumber(recBookNumber);

	if (student)
	{
		return *student;
	}

	throw std::runtime_error("Student is not found");
}
