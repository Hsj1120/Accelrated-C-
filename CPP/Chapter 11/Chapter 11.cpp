#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "Student_info.h"

using std::vector; using std::cout; using std::endl;
using std::string; using std::allocator; using std::uninitialized_fill;
using std::max;

template <class T> class Vec {
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef std::size_t size_type;
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;

	Vec() { create(); }
	explicit Vec(size_type n, const T& t= T()) { create(n, t); }
	
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
	if (data) { // data가 0이 아니면 역순으로 요소를 소멸시킴
		iterator it = avail;
		while (it != data)
			alloc.destroy(--it);
		
		// 할당된 모든 저장 공간을 반환
		alloc.deallocate(data, limit - data);
	}
	// 비어있는 Vec을 가리키도록 포인터를 재설정
	data = limit = avail = 0;
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
	alloc.construct(avail++, val);
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

int main()	
{
	
    
}
