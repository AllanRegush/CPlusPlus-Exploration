#include <iostream>

int main()
{
	std::cout << "Enter your first name and age" << std::endl;
	std::string first_name;
	double age = 0;
	std::cin >> first_name >> age;
	std::cout << "Hello, " << first_name << "(age " << age * 12 << " months" << ")\n";
	
	return 0;
}