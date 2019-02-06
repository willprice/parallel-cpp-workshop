#include <iostream>
#include <vector>
#include <cmath>
#include <mutex>

#include <tbb/parallel_for.h>


int main(int argc, char **argv)
{
    std::mutex m;

    auto values = std::vector<double>(10000);

    tbb::parallel_for(tbb::blocked_range<int>(0, values.size()),
      [&](tbb::blocked_range<int> r){
          m.lock();
          std::cout << "Range size " << (r.end() - r.begin())
                    << " from " << r.begin() << " to " << r.end() << std::endl;
          m.unlock();

          for (int i = r.begin(); i < r.end(); i++) {
              values[i] = std::sin(i * 0.001);
          };
    });

    double total = 0;

    for (auto value : values)
    {
        total += value;
    }

    std::cout << total << std::endl;

    return 0;
}
