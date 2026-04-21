#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using std::vector; using std::cout; using std::endl;
using std::sort; using std::domain_error; using std::swap;
using std::string; using std::find_if;

template <class T>
T median(vector<T> v)
{
    typedef typename vector<T>::size_type vec_sz;
    vec_sz size = v.size();
    if (size == 0)
        throw std::domain_error("median of an empty vector");
    std::sort(v.begin(), v.end());
    vec_sz mid = size / 2;
    return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
}

template <class In, class x>
In findx(In begin, In end, const x& value)
{
    while (begin != end && *begin != value)
        ++begin;
    return begin;
}

template <class In, class Out>
Out copy(In begin, In end, Out dest)
{
    while (begin != end)
        *dest++ = *begin++;
    return dest;
}

template <class For, class X>
void replace(For beg, For end, const X& x, const X& y)
{
    while (beg != end) {
        if (*beg == x)
            *beg = y;
        ++beg;
	}
}

template<class Bi>
void reverse(Bi beg, Bi end)
{
    while (beg != end) {
        --end;
        if (beg != end)
            swap(*beg++, *end);
    }
}

template<class Ran, class X>
bool binary_search(Ran begin, Ran end, const X& x)
{
    while (begin < end) {
        // 범위의 중간 지점 찾기
		Ran mid = begin + (end - begin) / 2;

        // 중간 지점을 기준으로 어느 부분이 x를 포함하는지 확인하고
        // 해당 부분에만 탐색을 진행
        if (x < *mid)
            end = mid;
        else if (*mid < x)
            begin = mid + 1;
		// 이 지점에 도달하면 *mid == x 이므로 탐색  종료
        else
			return true; // *mid == x
    }
}

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

template <class Out>
void split(const string& str, Out os)
{
    typedef string::const_iterator iter;
    iter i = str.begin();

	while (i != str.end()) {
        // 선행 공백 무시
        i = find_if(i, str.end(), not_space);

        // 다음 단어의 끝 찾기
		iter j = find_if(i, str.end(), space);

		// [i, j) 범위의 문자들을 복사
        if (i != str.end())
			*os++ = string(i, j);
        i = j;
    }
}


int main()
{
    string s;
    while (getline(std::cin, s)) 
		split(s, std::ostream_iterator<string>(std::cout, "\n"));
    return 0;
}
