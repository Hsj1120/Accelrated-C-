// Student_info 구조체와 관련된 함수들의 소스파일
#include "Student_info.h"

using std::vector; using std::istream;

bool compare(const Student_info& x, const Student_info& y)
{
	return x.name < y.name;
}

istream& read(istream& is, Student_info& s)
{
	is >> s.name >> s.midterm >> s.final;
	read_hw(is, s.homework);
	return is;
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

bool did_all_hw(const Student_info& s)
{
	return ((std::find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end());
}