#include <iostream>

template <class T>
static void do_something(T& item)
{
    item += 10;
}

int main()
{
    uint32_t item = 10;
    do_something(item);
    std::cout << item << std::endl;
    return 0;
}
