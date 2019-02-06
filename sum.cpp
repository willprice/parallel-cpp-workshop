#include <iostream>

int sum(int x, int y)
{
    return x + y;
}

int main(int argc, char **argv)
{
    int (*a)(int, int) = &sum;
    auto result = a(3, 7);
    std::cout << result << std::endl;
    return 0;
}
