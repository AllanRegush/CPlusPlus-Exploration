#include <iostream>
#include <string>
#include "employee.h"

int main()
{
    Employee employee;
    employee.do_something();
    std::string buff;
    std::getline(std::cin, buff);
    return 0;
}
