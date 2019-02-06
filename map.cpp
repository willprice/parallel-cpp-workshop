#include <iostream>
#include <vector>

int sum(int x, int y)
{
    return x + y;
}

int multiply(int x, int y)
{
    return x * y;
}

int difference(int x, int y)
{
    return x - y;
}

template<class T>
void print_vector(const std::vector<T> &values)
{
    std::cout << "[";

    for (const T &value : values)
    {
        std::cout << " " << value;
    }

    std::cout << " ]" << std::endl;
}

template<class Fn, class T>
auto map_fn(Fn fn, std::vector<T> &xs, std::vector<T> &ys)
{
    int len = std::min(xs.size(), ys.size());
    auto result = std::vector<T>(len);

    for (int i = 0; i < len; i++) {
      result[i] = fn(xs[i], ys[i]);
    }

    return result;
}

int main(int argc, char **argv)
{
    auto a = std::vector<int>( { 1, 2, 3, 4, 5 } );
    auto b = std::vector<int>( { 6, 7, 8, 9, 10 } );

    print_vector(map_fn(sum, a, b));
    print_vector(map_fn(difference, a, b));
    print_vector(map_fn(multiply, a, b));

    return 0;
}
