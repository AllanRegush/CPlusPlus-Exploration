#include <cstdio>

int main()
{
    float fahr, celsius;
    int lower = 0, upper = 300, step = 20;
    fahr = lower;
    std::printf("Celsius | Fahrenheit\n");
    std::printf("--------------------\n");
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        std::printf("%6.1f    %3.1f\n", celsius, fahr);
        fahr = fahr + step;
    }
}

