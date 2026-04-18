#include <iostream>
#include <string>
#include <map>
#include <vector>
using std::string; using std::map;
using std::cin; using std::cout; using std::endl;
using std::vector; using std::istream;

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

map<string, vector<int> > xref(istream& in,
vector<string> find_words(const string&) = split)
{
	string line;
	int line_number = 0;
	map<string, vector<int> > ret;

	// 다음 행을 읽음
	while (getline(in, line)) {
		++line_number;

		// 입력한 행을 단어로 나눔
		vector<string> words = find_words(line);

		// 현재 행에 등장한 모든 단어를 저장
		for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it)
			ret[*it].push_back(line_number);
	}
	return ret;
}

int main()
{
	map<string, vector<int> > ret = xref(cin);

	// 결과 출력
	for (map <string, vector<int> >::const_iterator it = ret.begin(); it != ret.end(); ++it) {
		// 단어를출력
		cout << it->first << " occurs on line(s): ";

		// 이어서 하나 이상의 행 번호를 출력
		vector<int>::const_iterator line_it = it->second.begin();
		cout << *line_it;
		++line_it;

		// 행 번호가 있으면 마저 출력
		while(line_it != it->second.end()) {
			cout << ", " << *line_it;
			++line_it;
		}

		cout << endl;
	}
	return 0;
}