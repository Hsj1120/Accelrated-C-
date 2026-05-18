#include <iostream>
#include <string>
#include <fstream>
using std::cout; using std::endl; using std::string;
using std::ifstream; using std::ofstream; using std::cerr;
using std::getline;

string letter_grade(double grade)
{
	// 각 범위를 구분하는 점수
	static const double numbers[] = { 97,94,90,87,84,80,77,74,70,60,0 };

	// 각 범위에 대응하는 학점
	static const char* const letters[] = { "A+","A","A-","B+","B","B-","C+","C","D+","D","F" };

	// 배열 크기와 요소 하나의 크기를 사용하요 각 범위를 구분하는 점수 개수를 구함
	static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

	// 주어진 최종 점수에 해당하는 문자 등급을 찾아서 반환
	for (size_t i = 0; i < ngrades; ++i) {
		if (grade >= numbers[i])
			return letters[i];
	}
	return "?\?\?";
}

int main(int argc, char** argv)
{
	int fail_count = 0;

	// 주어진 각 파일에 동작을 실행
	for (int i = 1; i < argc; ++i) {
		ifstream in(argv[i]);

		// 파일이 존재하면 해당 파일의 내용을 출력하고
		// 그렇지 않으면 오류 메시지를 출력
		if (in) {
			string s;
			while (getline(in, s)) {
				cout << s << endl;
			}
		}
		else {
			cerr << "파일 " << argv[i] << "을(를) 열 수 없습니다." << endl;
			++fail_count;
		}
	}
	return fail_count;
}
