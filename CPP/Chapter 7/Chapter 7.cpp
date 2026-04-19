#include <iostream>
#include <string>
#include <map>
#include <vector>
using std::string; using std::map;
using std::cin; using std::cout; using std::endl;
using std::vector; using std::istream;
using std::logic_error;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;


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

// 주어진 입력 스트림으로 문법 테이블을 읽음
Grammar read_grammar(istream& in)
{
	Grammar ret;
	string line;

	// 입력한 행을 모두 읽음
	while (getline(in, line)) {
		// 입력 데이터를 단어로 나눔
		vector<string> entry = split(line);
		if (!entry.empty())
			// 카테고리 및 연관된 규칙을 맵에 저장
			ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
	}
	return ret;
}

bool bracketed(const string& s)
{
	return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

void gen_aux(const Grammar& g, const string& word, vector<string>& ret)
{
	if (!bracketed(word)) {
		ret.push_back(word);
	} else {
		Grammar::const_iterator it = g.find(word);
		if (it == g.end())
			throw logic_error("empty rule");
		const Rule_collection& c = it->second;
		const Rule& r = c[nrand(c.size())];
		for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
			gen_aux(g, *i, ret);
	}
}

vector<string> gen_sentence(const Grammar& g)
{
	vector<string> ret;
	gen_aux(g, "<sentence>", ret);
	return ret;
}

int main()
{
	// 문장 생성
	vector <string> sentence = gen_sentence(read_grammar(cin));

	// 첫번째 단어 출력
	vector<string>::const_iterator it = sentence.begin();
	if (!sentence.empty()) {
		cout << *it;
		++it;
	}

	// 공백과 함께 나머지 단어 출력
	while (it != sentence.end()) {
		cout << " " << *it;
		++it;
	}
	cout << endl;

	return 0;
}