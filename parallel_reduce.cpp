#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <mutex>

#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>

int main(int argc, char **argv)
{
  auto total = tbb::parallel_reduce(
      tbb::blocked_range<int>(0, 10000),
      0.0,
      [&](tbb::blocked_range<int> r, double running_total) {
        for (int i = r.begin(); i < r.end(); i++) {
          running_total += std::sin(i * 0.001);
        }
        return running_total;
      }, std::plus<double>());
  std::cout << total << std::endl;
}
