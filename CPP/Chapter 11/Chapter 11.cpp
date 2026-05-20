#include <iostream>
#include <vector>
#include "Student_info.h"

using std::vector; using std::cout; using std::endl;

template <class T> 
class vec {
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef std::size_t size_type;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef T& reference;
	typedef const T& const_reference;

	vec() {create(n)}
	explicit Vec(std::size_t n, const T& val = T()) { create(n, val); }
	Vec(const Vec& v){create(v.begin(), v.end()); }
	
	// 새로운 함수
	size_type size() const { return limit - data; }
	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) const { return data[i]; }

	// 반복자를 반환하는 새로운 함수
	iterator begin() { return data; }
	const_iterator begin() const { return data; }

	iterator end() { return limit; }
	const_iterator end() const { return limit; }

private:
	T* data; // Vec의 첫 번쨰 요소를 가리키는 포인터
	T* limit; // Vec의 마지막 요소 다음을 가리키는 포인터
};

int main()	
{
	vector<Student_info> vs; // 빈 벡터
	vector<double> v(100); // 100개의 요소를 가진 벡터

	// 벡터가 사용하는 타입의 이름을 얻음
	vector<Student_info>::const_iterator b, e;
	vector<Student_info>::size_type i = 0;

	// size 함수와 인덱스 연산자를 사용하여 벡터의 각 요소를 탐색
	for (i = 0; i < vs.size(); ++i)
		cout << vs[i].name() << endl;

	b = vs.begin();
	e = vs.end();
    
}
