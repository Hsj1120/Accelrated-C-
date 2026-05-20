#ifndef GUARD_Student_INFO_H
#define GUARD_Student_INFO_H

// String_info.h
#include <iostream>
#include <string>
#include <vector>

class Student_info {
public:
	Student_info(); // 빈 Student_info 객체를 생성
	Student_info(std::istream&); // 스트림을 읽어서 Student_info 객체를 생성
	std::string name() const { return n; }
	bool valid() const { return !homework.empty(); }

	// 9.2.1에서 정의한 read 함수에서 name을 n으로 변경 필요
	std::istream& read(std::istream&);

	// 9.2.1 에서 정의한 것과 같음
	double grade() const;
	
private:
	std::string n;
	double midterm, final;
	std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream& is, Student_info& s);
std::istream& read_hw(std::istream& in, std::vector<double>& hw);
#endif