#ifndef GUARD_STRING_INFO_H
#define GUARD_STRING_INFO_H
// grade.h
#include <vector>
#include "Student_info.h"

double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double grade(const Student_info&);
double grade_aux(const Student_info&);
double average(const std::vector<double>&);
double average_grade(const Student_info&);
double optimistic_median(const Student_info&);
#endif