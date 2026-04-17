#include<vector>
#include<iostream>
#include<string>
#include<cctype>
#include <algorithm>

#include "Student_info.h"
#include "median.h"
#include "grade.h"
using std::cin; using std::cout; using std::endl;
using std::vector; using std::string;
using std::max; using std::copy;
using std::equal; using std::find_if;
using std::ostream; using std::back_inserter;

// 인수가 공백일 때는 true, 그렇지 않을 때는 false를 반환하는 함수
bool space(char c)
{
	return isspace(c);
}

// 인수가 공백일 때는 false, 그렇지 않을 때는 true를 반환하는 함수
bool not_space(char c)
{
	return !isspace(c);
}

vector<string> split(const string& str)
{
	typedef string::const_iterator iter;
	vector<string> ret;
	iter i = str.begin();

	while (i != str.end()) {
		// 선행 공백을 무시
		i = find_if(i, str.end(), not_space);

		// 다음 단어의 끝을 찾음
		iter j = find_if(i, str.end(), space);
		
		// [i, j) 범위의 문자들을 복사
		if (i != str.end())
			ret.push_back(string(i, j));
		i = j;
	}
	return ret;
}

bool is_palindrome(const string& s)
{
	return equal(s.begin(), s.end(), s.rbegin());
}

bool not_url_char(char c)
{
	// URL에 포함될 수 있는 문자를 나열한 문자열
	static const string url_ch = "~;/?:@=&$-_.+!*'(),";

	// c가 URL에 들어갈 수 있는 문자인지 확인하면 음수를 반환
	return !(isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator url_end(string::const_iterator b, string::const_iterator e)
{
	return find_if(b, e, not_url_char);
}

string::const_iterator url_beg(string::const_iterator b, string::const_iterator e)
{
	static const string sep = "://";
	typedef string::const_iterator iter;

	// i는 구분 기호를 발견한 위치를 표시
	iter i = b;
	while ((i = search(i, e, sep.begin(), sep.end())) != e) {
		// 구분 기호가 현재  탑색 범위의 처음 또는 마지막에 있는지 확인
		if (i != b && i + sep.size() != e) {
			// beg은 프로토콜 이름의 시작 위치를 표시
			iter beg = i;
			while (beg != b && isalnum(beg[-1]))
				--beg;

			if (beg != i && not_url_char(i[sep.size()]))
				return beg;
		}
		i += sep.size();
	}
	return e;
}


vector<string> find_urls(const string& s)
{
	vector<string> ret;
	typedef string::const_iterator iter;
	iter b = s.begin(), e = s.end();

	//인수로 전달받은 문자열 전체를 탐색
	while (b != e) {
		// :// 앞쪽에서 하나 이상의 문자를 탐색
		b = url_beg(b, e);
		if (b != e) {
			// 해당 문자를 찾았다면 나머지 부분을 탐색
			iter after = url_end(b, e);

			// URL을 저장
			ret.push_back(string(b, after));

			// 인수로 전달받은 문자열에서 또 다른 URL을 찾기 위해 b를 증가
			b = after;
		}
	}
	return ret;
}


double median_analysis(const vector<Student_info>& students)
{
	vector<double> grades;
	transform(students.begin(), students.end(), back_inserter(grades), grade_aux);
	return median(grades);
}

double average_analysis(const vector<Student_info>& students)
{
	vector<double> grades;
	transform(students.begin(), students.end(), back_inserter(grades), average_grade);
	return median(grades);
}

double optimistic_median_analysis(const vector<Student_info>& students)
{
	vector<double> grades;
	transform(students.begin(), students.end(), back_inserter(grades), optimistic_median);
	return median(grades);
}

void write_analysis(ostream& out, const string& name,
	double analysis(const vector<Student_info>&), const vector<Student_info>&  did, const vector<Student_info>& didnt)
{
	out << name << ": median(did) = " << analysis(did) <<
		", median(didnt) = " << analysis(didnt) << endl;
}

int main()
{
	vector<Student_info> did, didnt;
	Student_info students;

	// 학생 정보를 읽고 과제를 모두 제출한 학생과 그렇지 않은 학생을 구분하여 저장
	while (read(cin, students)) {
		if (did_all_hw(students))
			did.push_back(students);
		else
			didnt.push_back(students);
	}


	// 두 집단에 데이터가 있는지 확인
	if (did.empty()) {
		cout << "No student did all the homework!" << endl;
		return 1;
	}

	if (didnt.empty()) {
		cout << "Every student did all the homework!" << endl;
		return 1;
	}

	write_analysis(cout, "median", median_analysis, did, didnt);
	write_analysis(cout, "average", average_analysis, did, didnt);
	write_analysis(cout, "median of homework turned in", optimistic_median_analysis, did, didnt);
}