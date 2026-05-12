#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "student_info.h"

using std::vector; using std::cin; using std::cout; using std::endl;
using std::string; using std::sort; using std::streamsize; using std::setprecision;


int main()
{
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;

	// 데이터를 읽어 저장
	while (record.read(cin)) {
		maxlen = std::max(maxlen, record.name().size());
		students.push_back(record);
	}

	// 학생 정보를 알파벳 순으로 정렬
	sort(students.begin(), students.end(), compare);

	// 이름과 점수를 출력
	for (vector<Student_info>::size_type i = 0; i < students.size(); ++i) {
		cout << students[i].name()
			 << string(maxlen + 1 - students[i].name().size(), ' ');
		try {
			double final_grade = students[i].grade();
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec);
		} catch (std::domain_error e) {
			cout << e.what();
		}
		cout << endl;
	}
	return 0;
}
