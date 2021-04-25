#include <iostream>

[[nodiscard]]static int32_t add(int32_t a, int32_t b)
{
    return a + b;
}

[[nodiscard]] static uint32_t add(uint32_t a, uint32_t b)
{
    return a + b;
}


int main()
{
    auto result_of_add_one = add(10, 10);
    auto result_of_add_two = add(-10, 10);
    std::cout << result_of_add_one << ' ' << result_of_add_two << '\n';
    return 0;
}
