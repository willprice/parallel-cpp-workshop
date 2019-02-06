
#include "part1.h"

using namespace part1;

int main(int argc, char **argv)
{
    auto a = std::vector<int>( { 1, 2, 3, 4, 5 } );
    auto b = std::vector<int>( { 6, 7, 8, 9, 10 } );

    auto result = parallel::mapReduce( std::multiplies<int>(),
                                       std::plus<int>(), 
                                       a, b );

    if (result == 130)
    {
        std::cout << "Everything is ok :-)" << std::endl;
    }
    else
    {
        std::cout << "Something went wrong? " << result << std::endl;
    }

    return 0;
}

