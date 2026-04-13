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