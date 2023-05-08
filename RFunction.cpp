#include "RFunction.h"


double R(std::vector<double> x, const int parameters_amount)
{
    double result = -(x[1] + 47) * std::sin(std::sqrt(std::abs(x[1] + x[0] / 2 + 47))) - x[0] * std::sin(std::sqrt(std::abs(x[1] - x[0] - 47)));
    return result;
}