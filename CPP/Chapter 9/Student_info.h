#ifndef GUARD_Student_INFO_H
#define GUARD_Student_INFO_H

// String_info.h
#include <iostream>
#include <string>
#include <vector>

struct Student_info {
	std::string name;
	double midterm, final;
	std::vector<double> homework;

	std::istream& read(std::istream&);
	double grade() const;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream& is, Student_info& s);
std::istream& read_hw(std::istream& in, std::vector<double>& hw);

#endif