// Student_info 구조체와 관련된 함수들의 소스파일
#include "Student_info.h"
#include "grade.h"
using std::vector; using std::istream;
using std::cout; using std::remove_copy_if;
using std::erase; using std::remove_if;
using std::stable_partition;

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

bool fgrade(const Student_info& s)
{
	return grade(s) < 60;
}

bool pgrade(const Student_info& s)
{
	return !fgrade(s);

}
/* 
// 벡터를 두 번 탐색하는 방식
vector<Student_info> extract_fails(vector<Student_info>& students)
{
	vector<Student_info> fails;
	remove_copy_if(students.begin(), students.end(),
		back_inserter(fails), pgrade);

	students.erase(remove_if(students.begin(), students.end(), fgrade),
		students.end());

	return fails;
}
*/

vector<Student_info> extract_fails(vector<Student_info>& students)
{
	vector<Student_info>::iterator iter = stable_partition(students.begin(), students.end(), pgrade);
	vector<Student_info> fails(iter, students.end());
	students.erase(iter, students.end());
	return fails;
}