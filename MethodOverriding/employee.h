#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include "person.h"

class Employee : Person
{
public:
    Employee();
    void do_something() override;
};

#endif // EMPLOYEE_H
