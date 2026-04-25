#include <vector>
#include <iostream>
#include <string>
using std::vector;
using std::string;

struct Student_info {
	std::string name;
	double midterm, final;
	std::vector<double> homework;

	std::istream& read(std::istream&);
	double grade() const;
};

int main()
{
    std::cout << "Hello World!\n";
}