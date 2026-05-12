// Student_info 구조체와 관련된 함수들의 소스파일
#include "Student_info.h"

using std::vector; using std::istream;

bool compare(const Student_info& x,	const Student_info& y)
{
	return x.name() < y.name();
}

istream& read_hw(istream& in, vector<double>& hw)
{
	if (in) {
		hw.clear();

		double x;
		while (in >> x)
			hw.push_back(x);

		in.clear();
	}
	return in;
}

istream& Student_info::read(istream& is)
{
	is >> n >> midterm >> final;
	read_hw(is, homework);
	return is;
}

Student_info::Student_info() : midterm(0), final(0) {}
Student_info::Student_info(std::istream& is) { read(is); }