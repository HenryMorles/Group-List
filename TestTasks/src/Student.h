#pragma once

#include <string>

enum Specialization 
{
	MATHEMATICS,
	PHYSICS,
	ECONOMICS,
	COMPUTER_SCIENCE
};

class Student
{
public:

	std::string _firstName;
	std::string _lastName;
	Specialization _specialization;
	int _recBookNumber;

	Student(std::string firstName, std::string lastName, Specialization specialization, int recBookNumber);
};

