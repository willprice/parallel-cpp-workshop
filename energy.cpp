#include "part1.h"
#include <functional>

using namespace part1;

double calculate_energy(const Point &point1,
                        const Point &point2)
{
    return 1.0 / (0.1 + calc_distance(point1, point2));
}

double calculate_energy(const std::vector<Point> &group1,
                        const std::vector<Point> &group2)
{
    double total = 0;

    for (const Point &point1 : group1)
    {
        for (const Point &point2 : group2)
        {
            total += calculate_energy(point1, point2);
        }
    }

    return total;
}

double mapreduce_energy(const std::vector<Point> &group1,
                        const std::vector<Point> &group2)
{
    return parallel::mapReduce( [=](const Point &point1)
                      {
                          return mapReduce([=](const Point &point2)
                          {
                              return calculate_energy(point1, point2);
                          },
                          std::plus<double>(), group2 );
                      },
                      std::plus<double>(), group1 );
}

int main(int argc, char **argv)
{
    auto group_a = create_random_points(20000);
    auto group_b = create_random_points(20000);

    auto t0 = tbb::tick_count::now();
    auto energy = calculate_energy(group_a, group_b);
    auto t1 = tbb::tick_count::now();

    std::cout << "Total energy = " << energy << std::endl;
    std::cout << "Took = " << (t1-t0).seconds() << " seconds" << std::endl;

    t0 = tbb::tick_count::now();
    energy = mapreduce_energy(group_a, group_b);
    t1 = tbb::tick_count::now();

    std::cout << "Map/Reduce energy = " << energy << std::endl;
    std::cout << "Took = " << (t1-t0).seconds() << " seconds" << std::endl;

    return 0;    
}
