#include <iostream>
using std::cout; using std::endl;

int next(int n)
{
	return n + 1;

}

int main()
{
	int i = 0;
	int (*fp)(int) = next; // fp는 next 함수를 가리킴

	fp = next; // fp는 next 함수를 가리킴

	i = fp(i); 
	cout << "i = " << i << endl;

	i = (*fp)(i); 
	// p를 통해 x의 값을 변경
	cout << "i = " << i << endl;

	return 0;
}