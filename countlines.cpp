#include "filecounter.h"
#include "part1.h"

using namespace part1;
using namespace filecounter;

int main(int argc, char** argv) {
    auto file_paths = get_arguments(argc, argv);
    auto line_counts = map(count_lines, file_paths);
    auto total_line_count = reduce([](int a, int b) { return a + b; }, line_counts);
    std::cout << "Total line count: " << total_line_count << std::endl;
    for (int i = 0; i < file_paths.size(); i++) {
        std::cout << file_paths[i] << ": " << line_counts[i] << std::endl;
    }
    return 0;
}
