#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "Student_info.h"

using std::vector; using std::cout; using std::endl;
using std::string; using std::allocator; using std::uninitialized_fill;
using std::max; using std::istream; using std::ostream; using std::uninitialized_copy;
template <class T> class Vec {
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef std::size_t size_type;
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;

	Vec() { create(); }
	explicit Vec(size_type n, const T& t = T()) { create(n, t); }

	Vec(const Vec& v) { create(v.begin(), v.end()); }
	Vec& operator=(const Vec& v); //11.3.2에서 정의
	~Vec() { uncreate(); }

	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) const { return data[i]; }

	void push_back(const T& val) {
		if (avail == limit)
			grow();

		unchecked_append(val);
	}

	size_type size() const { return avail - data; } // 변경됨

	iterator begin() { return data; }
	const_iterator begin() const { return data; }

	iterator end() { return avail; } // 변경됨
	const_iterator end() const { return avail; }
	void clear() { uncreate(); }

private:
	iterator data; // Vec의 첫 번쨰 요소를 가리키는 포인터
	iterator avail; // Vec의 마지막 요소의 다음을 가리키는포인터
	iterator limit; // 사용할 수 있는 마지막 요소의 다음을 가리키는 포인터

	// 메모리 할당을 위한 기능
	allocator<T> alloc; // 메모리 할당을 다루는 객체

	// 기저 배열의 할당 및 초기화
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	// 배열에 있는 요소들을 소멸시키고 메모리를 해제
	void uncreate();

	// push_back 함수를 지원하는 함수
	void grow();
	void unchecked_append(const T&);
};

template <class T> void Vec<T>::create()
{
	data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val)
{
	data = alloc.allocate(n); // n개의 요소를 위한 메모리를 할당
	limit = avail = data + n; // limit은 마지막 요소의 다음을 가리킴
	uninitialized_fill(data, limit, val);
}

template <class T> void Vec<T>::create(const_iterator i, const_iterator j)
{
	data = alloc.allocate(j - i); // i와 j 사이의 요소를 위한 메모리를 할당
	limit = avail = uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::uncreate()
{
	if (data) {
		iterator it = avail;
		while (it != data) {
			// alloc.destroy(--it); 대신 아래와 같이 작성한다.
			std::allocator_traits<std::allocator<T>>::destroy(alloc, --it);
		}

		// 할당된 모든 저장 공간을 반환
		alloc.deallocate(data, limit - data);
	}
	// 포인터 재설정 (현대 C++ 스타일인 nullptr 사용 권장)
	data = limit = avail = nullptr;
}

template <class T> void Vec<T>::grow()
{
	// 새로 할당할 메모리의 크기는 현재 크기의 2배
	size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

	// 새 메모리를 할당하고 기존 요소를 새 메모리로 복사
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = uninitialized_copy(data, avail, new_data);

	// 기존 요소를 소멸시키고 기존 메모리를 해제
	uncreate();
	// 새 데이터로 포인터를 재설정
	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}

// avail은 할당되었지만 아직 초기화 하지 않은 저장 공간을 가리킨다고 가정
template <class T> void Vec<T>::unchecked_append(const T& val)
{
	std::allocator_traits<std::allocator<T>>::construct(alloc, avail++, val);
}

template <class T> Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
	// 자가 할당 여부 확인
	if (&rhs != this) {
		//좌변이 지닌 배열이 점유하는 메모리를 해제
		uncreate();

		// 우변이 지닌 요소를 좌변으로 복사
		create(rhs.begin(), rhs.end());
	}
	return *this;
}

class Str {
friend istream& operator >> (istream&, Str&);

public:
	Str& operator+= (const Str& s) {
		std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
		return *this;
	}

	typedef Vec<char>::size_type size_type;

	// 비어 있는 Str 객체를 만드는 기본 생성자
	Str() {}

	// c의 복사본 n개가 있는 Str 객체를 생성
	Str(size_type n, char c) : data(n, c) {}

	// null로 끝나는 char 타입의 배열에서 Str 객체를 생성
	Str(const char* cp) {
		std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
	}

	// 반복자 b와 e가 가리키는 char 타입의 요소에서 Str 객체를 생성
	template<class In> Str(In b, In e) {
		std::copy(b, e, std::back_inserter(data));
	}

	char& operator[] (size_type i) { return data[i]; }
	const char& operator[] (size_type i) const { return data[i]; }
	size_type size() const { return data.size(); }

private:
	Vec<char> data;
};

Str operator + (const Str& s, const Str& t)
{
	Str r = s;
	r += t;
	return r;
}

istream& operator >> (istream& is, Str& s)
{
	// 기존의 값 제거
	s.data.clear(); 
	char c;

	// 조건을 판별하는 것 외의 동작은 없음
	while (is.get(c) && !isspace(c));

	// 읽을 문자가 남아 있다면 다음 공백 문자에 도달할 때까지 문자를 읽음
	if (is) {
		do s.data.push_back(c);
		while (is.get(c) && !isspace(c));

		// 공백을 읽었다면 다시 스트림에 남겨둠
		if (is)	
			is.unget();
	}
	return is;
}

ostream& operator << (ostream& os, const Str& s)
{
	for (Str::size_type i = 0; i < s.size(); i++)
	{
		os << s[i];
	}
	return os;
}

int main()
{

}
