#include <iostream>
#include <string>

// 표준 라이브러리에서 사용할 이름을 언급
using std::cout; using std::string;
using std::cin; using std::endl;

int main()
{	
	// 이름을 물음
	cout << "Please enter your first name : ";

	// 이름을 입력
	string name;
	cin >> name;

	// 출력하려는 메시지를 구성
	const string greeting = "Hello, " + name + "!";

	// 인사말과 한쪽 테두리 사이의 공백 개수
	const int pad = 1;

	// 출력할 행의 전체 개수
	const int rows = pad * 2 + 3;
	const string::size_type cols = greeting.size() + pad * 2 + 2;

	// 입력과 출력을 구분
	cout << endl;

	//rows개 행을 출력한다.
	// 불변성: 지금까지 r개 행을 출력
	for (int r = 0; r != rows; ++r)
	{
		string::size_type c = 0;
		// 불변성: 현재 행에서 c개의 문자를 출력
		while(c != cols)
		{
			if(r == pad + 1 && c == pad + 1)
			{
				cout << greeting;
				c += greeting.size();
			}
			else
			{
				if(r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
					cout << "*";
				else
					cout << " ";
				++c;
			}
		}
		cout << endl;
	}
	// 다시 작성할 부분
	return 0;
}

