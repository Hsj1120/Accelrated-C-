#include <iostream>
#include <string>
using std::cout; using std::endl; using std::string;

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
	// 명령 프롬프트에 입력한 인수가 존재하면 출력
	if (argc > 1) {
		int i;
		for (i = 1; i < argc-1; ++i)
			cout << argv[i] << " ";
		cout << argv[i] << endl;
	}
	return 0;
}