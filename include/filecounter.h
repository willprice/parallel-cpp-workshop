#ifndef filecounter_h
#define filecounter_h

#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <string>
#include <fstream>

namespace filecounter
{

/** This function counts the number of lines in the file called 'filename' */
int count_lines(const std::string &filename)
{
    std::ifstream file( filename );

    int nlines = 0;

    std::string str;
    while (std::getline(file, str))
    {
        nlines += 1;
    }

    return nlines;
}

/** This function converts a set of arguments into a set of strings */
std::vector<std::string> get_arguments(int argc, char **argv)
{
    if (argc < 2)
    {
        return std::vector<std::string>();
    }

    auto args = std::vector<std::string>(argc-1);

    for (int i=1; i<argc; ++i)
    {
        args[i-1] = argv[i];
    }

    return args;
}

} // end of namespace filecounter

#endif

