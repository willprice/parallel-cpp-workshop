#include <iostream>
#include <vector>
#include <functional>

#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>

template<class MapFn, class ReduceFn>
auto mapReduce(MapFn map_fn, ReduceFn reduce_fn, 
               const std::vector<int> &arg1,
               const std::vector<int> &arg2) {
  int vals_count = std::min(arg1.size(), arg2.size());
  return tbb::parallel_reduce(
      tbb::blocked_range<int>(0, vals_count),
      0,
      [&](tbb::blocked_range<int> r, int running_total) {
        for (int i = r.begin(); i < r.end(); i++) {
          running_total = reduce_fn(running_total, map_fn(arg1[i], arg2[i]));
        }
        return running_total;
      }, reduce_fn);
}

int main(int argc, char **argv) {
  auto a = std::vector<int>({1, 2, 3, 4, 5});
  auto b = std::vector<int>({6, 7, 8, 9, 10});
  auto result = mapReduce(std::multiplies<int>(),
                          std::plus<int>(), a, b);
  std::cout << result << std::endl;
  return 0;
}
