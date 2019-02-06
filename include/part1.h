#ifndef part1_h
#define part1_h

#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <string>
#include <fstream>
#include <random>

#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/tick_count.h>

namespace part1
{

namespace detail
{
    template<class ARG>
    size_t get_min_container_size(const std::vector<ARG> &arg)
    {
        return arg.size();
    }

    template<class ARG1, class ARG2>
    size_t get_min_container_size(const std::vector<ARG1> &arg1, const std::vector<ARG2> &arg2)
    {
        return std::min(arg1.size(), arg2.size());
    }

    template<class ARG1, class ARG2, class... ARGS>
    size_t get_min_container_size(const std::vector<ARG1> &arg1, const std::vector<ARG2> &arg2,
                                  const std::vector<ARGS>&... args)
    {
        size_t minsize = get_min_container_size(args...);
        return std::min( minsize, get_min_container_size(arg1,arg2) );
    }

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);
}

/** This will map the function 'func' against the array(s) of argument(s) in args,
    returning a vector of results */
template<class FUNC, class... ARGS>
auto map(FUNC func, const std::vector<ARGS>&... args)
{
    typedef typename std::result_of<FUNC(ARGS...)>::type RETURN_TYPE;

    int nvals=detail::get_min_container_size(args...);

    std::vector<RETURN_TYPE> result(nvals);

    for (size_t i=0; i<nvals; ++i)
    {
        result[i] = func(args[i]...);
    }

    return result;
}

/** This will reduce the passed array of values using the function 'func' */
template<class FUNC, class T>
T reduce(FUNC func, const std::vector<T> &values)
{
    if (values.empty())
    {
        return T();
    }
    else
    {
        T result = values[0];

        for (size_t i=1; i<values.size(); ++i)
        {
            result = func(result, values[i]);
        }

        return result;
    }
}

/** This will reduce the passed array of values using the function 'func',
    starting from the initial value 'initial' */
template<class FUNC, class T>
T reduce(FUNC func, const std::vector<T> &values, const T &initial)
{
    if (values.empty())
    {
     	return initial;
    }
    else
    {
     	T result = initial;

        for (const T &value : values)
        {
            result = func(result, value);
        }

	return result;
    }
}

/** This will map the passed function onto the passed vector(s)
    of argument(s), and will use the passed reduction function to
    reduce the result */
template<class MAPFUNC, class REDFUNC, class... ARGS>
auto mapReduce(MAPFUNC mapfunc, REDFUNC redfunc, const std::vector<ARGS>&... args)
{
    typedef typename std::result_of<MAPFUNC(ARGS...)>::type RETURN_TYPE;
     
    int nvals=detail::get_min_container_size(args...);

    if (nvals == 0)
    {
        return RETURN_TYPE();
    }

    RETURN_TYPE result = mapfunc(args[0]...);

    if (nvals == 1)
    {
        return result;
    }
         
    for (size_t i=1; i<nvals; ++i)
    {
        result = redfunc( result, mapfunc(args[i]...) );
    }
     
    return result;
}

namespace parallel
{

template<class MAPFUNC, class REDFUNC, class... ARGS>
auto mapReduce(MAPFUNC mapfunc, REDFUNC redfunc, const std::vector<ARGS>&... args)
{
    typedef typename std::result_of<MAPFUNC(ARGS...)>::type RETURN_TYPE;

    int nvals=detail::get_min_container_size(args...);

    RETURN_TYPE result =
         tbb::parallel_reduce( tbb::blocked_range<int>(0,nvals),
                               RETURN_TYPE(0),
               [&](tbb::blocked_range<int> r, RETURN_TYPE task_result)
         {
             for (int i=r.begin(); i<r.end(); ++i)
             {
                 task_result = redfunc(task_result, mapfunc(args[i]...) );
             }

             return task_result;

         }, redfunc );

    return result;                               
}

} // end of namespace parallel

/** This prints the elements of a vector to the screen */
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

/** This is a simple 3D point class */
class Point
{
public:
    Point() : x(0), y(0), z(0)
    {}

    Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
    {}

    float x, y, z;
};

/** This function calculates the distance between points */
float calc_distance(const Point &p1, const Point &p2)
{
    const float dx = p1.x - p2.x;
    const float dy = p1.y - p2.y;
    const float dz = p1.z - p2.z;

    return std::sqrt(dx*dx + dy*dy + dz*dz);
}


/** Return a vector of 'n' randomly positoned points, located
    in a cubic box of size 'sz' */
auto create_random_points(int n, float sz=50.0)
{
    auto points = std::vector<Point>(n);

    for (int i=0; i<n; ++i)
    {
        points[i] = Point(sz * detail::distribution(detail::generator),
                          sz * detail::distribution(detail::generator),
                          sz * detail::distribution(detail::generator) );
    }

    return points;
}

} // end of namespace part1

#endif

