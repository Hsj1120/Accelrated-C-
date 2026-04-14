#include<vector>
#include<iostream>
#include<string>
#include<cctype>
#include <algorithm>

using std::cin; using std::cout; using std::endl;
using std::vector; using std::string;
using std::max;

vector<string> split(const string& s)
{
	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		// 선행하는 공백들을 부시

		//불변성 : [원래의 i, 현재의 i) 범위에 있는 문자들은 모두 공백
		while (i != s.size() && isspace(s[i]))
			++i;

		// 순서상 다음 단어의 끝을 찾음
		string::size_type j = i;

		//불변성 : [현재의 j, 다음의 j) 범위에 있는 문자들은 모두 공백이 아님
		while (j != s.size() && !isspace(s[j]))
			++j;

		//공백이 아닌 문자들을 찾았을 때
		if (i != j) {
			// i부터 j-i개의 문자를 s에 복사
			ret.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}

string::size_type width(const vector<string>& v)
{
	string::size_type maxlen = 0;
	for (vector<string>::size_type i = 0; i != v.size(); ++i)
		maxlen = max(maxlen, v[i].size());
	return maxlen;
}

vector <string> frame(const vector<string>& v)
{
	vector<string> ret;
	string::size_type maxlen = width(v);
	string border(maxlen + 4, '*');

	// 상단 테두리를 추가
	ret.push_back(border);
	
	// 양 끝이 별표와 공백으로 둘러싸인 문자열들을 각각 추가
	for (vector<string>::size_type i = 0; i != v.size(); ++i)
		ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + " *");
	
	// 하단 테두리를 추가
	ret.push_back(border);
	return ret;
}

vector<string> vcat(const vector<string>& top, const vector<string>& bottom)
{
	// 위쪽 문자 그림을 복사
	vector<string> ret = top;

	//아래쪽 문자 그림을 복사
	for(vector<string>::const_iterator it = bottom.begin(); it != bottom.end(); ++it)
		ret.push_back(*it);
	return ret;
}

vector <string> hcat(const vector<string>& left, const vector<string>& right)
{
	vector<string> ret;

	// 두 문자 그림 사이에 공백을 하나 남김
	string::size_type width1 = width(left) + 1;
	
	// 왼쪽 문자 그림과 오른쪽 문자 그림의 요소를 살펴보는 인덱스
	vector<string>::size_type i = 0, j = 0;

	// 두 문자 그림의 모든 행을 살펴봄
	while (i != left.size() || j != right.size()) {

		// 두 문자 그림의 문자들을 처리할 새로운 문자를 생성
		string s;

		// 왼쪽 문자 그림에서 행 하나를 복사
		if (i != left.size())
			s = left[i++];

		// 공백을 포함하여 문자열을 적절한 너비까지 채움
		s = string(width1, ' ');


		// 오른쪽 문자 그림에서 행하나를 복사
		if (j != right.size())
			s += right[j++];

		//새로운 문자 그림에 문자열 s를 추가
		ret.push_back(s);
	}
	return ret;
}

int main()
{
	string s;
	while (getline(cin, s)) {
		vector<string> v = split(s);
		vector<string> f = frame(v);

		for (vector<string>::size_type i = 0; i != f.size(); ++i)
			cout << f[i] << endl;
	}
}