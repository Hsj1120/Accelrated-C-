#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "grade.h"
#include "Student_info.h"

using std::cin; using std::setprecision;
using std::cout;  using std::sort;
using std::domain_error; using std::streamsize;
using std::string; using std::endl;
using std::max; using std::vector;

int main()
{
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0; // 학생 이름의 최대 길이


	// 학생의 이름과 모든 점수를 읽어 저장하고 가장 긴 이름을 찾음
	while (read(cin, record)) {
		maxlen = max(maxlen, record.name.size());
		students.push_back(record);
	}

	// 학생들을 이름순으로 정렬
	sort(students.begin(), students.end(), compare);

	for (vector<Student_info>::size_type i = 0; i < students.size(); ++i) {
		cout << students[i].name << string(maxlen + 1 - students[i].name.size(), ' '); // 이름과 점수 사이에 공백 추가
		try {
			double final_grade = grade(students[i]);
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec);
		} catch (domain_error e) {
			cout << e.what();
		}
		cout << endl;
	}
	return 0;
}