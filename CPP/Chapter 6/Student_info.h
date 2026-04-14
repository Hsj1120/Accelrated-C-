#ifndef GUARD_Student_INFO_H
#define GUARD_Student_INFO_H

// String_info.h
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Student_info {
	std::string name;
	double midterm, final;
	std::vector<double> homework;
}; // 세미콜론 있어야 함

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream& is, Student_info& s);
std::istream& read_hw(std::istream& in, std::vector<double>& hw);
bool did_all_hw(const Student_info& s);
#endif