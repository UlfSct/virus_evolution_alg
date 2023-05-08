#include "Virus.h"


void Virus::updateFitnessValue
(
    const int parameters_amount,
    const int individual_parameter_size,
    const double parameters_min_values[PARAMETERS_AMOUNT],
    const double parameters_max_values[PARAMETERS_AMOUNT])
{
    if (data.size() == 0)
        return;

    std::vector<double> x;

    for (int k = 0; k < parameters_amount; k++)
    {
        x.push_back(getRealParameterValue(k, individual_parameter_size, parameters_max_values[k], parameters_min_values[k]));
    }
    this->fitness = R(x, parameters_amount);
}


double Virus::getRealParameterValue(int k, const int individual_parameter_size, const double max_value, const double min_value)
{
    int pow_exp = 0;
    int binary_in_real_value = 0;
    for (int i = k * individual_parameter_size + individual_parameter_size - 1; i >= k * individual_parameter_size; i--)
    {
        binary_in_real_value += data[i] * std::pow(2, pow_exp);
        pow_exp++;
    }
    return (min_value + (max_value - min_value) * (binary_in_real_value / (std::pow(2, individual_parameter_size) - 1)));
}


Virus::Virus()
{
    iterations_in_elite_group = -1;
    iterations_in_strain = -1;
    is_strain = false;
}


Virus::Virus
(
    std::vector<bool> data,
    const int parameters_amount,
    const int individual_parameter_size,
    const double parameters_min_values[PARAMETERS_AMOUNT],
    const double parameters_max_values[PARAMETERS_AMOUNT]
)
{
    this->data = data;
    iterations_in_elite_group = 0;
    iterations_in_strain = 0;
    is_strain = false;

    updateFitnessValue(parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values);
}


Virus::~Virus()
{
    data.clear();
}


std::vector<bool> Virus::getData()
{
    return this->data;
}


double Virus::getFitness()
{
    return this->fitness;
}


bool Virus::isStrain()
{
    return is_strain;
}


void Virus::increaseIterationsInEliteGroup()
{
    this->iterations_in_elite_group++;
}


void Virus::increaseIterationsInStrain()
{
    this->iterations_in_strain++;
}


int Virus::getIterationsInElite()
{
    return this->iterations_in_elite_group;
}


int Virus::getIterationsInStrain()
{
    return this->iterations_in_strain;
}


void Virus::strainStatusChange()
{
    this->is_strain = !(this->is_strain);
    this->iterations_in_strain = 0;
}


void Virus::zeroingIterations()
{
    this->iterations_in_strain = 0;
    this->iterations_in_elite_group = 0;
}


void Virus::printResults(
    const int parameters_amount,
    const int individual_parameter_size,
    const double parameters_min_values[PARAMETERS_AMOUNT],
    const double parameters_max_values[PARAMETERS_AMOUNT])
{
    for (int i = 1; i <= parameters_amount; i++)
    {
        std::cout << "Optimized x" << i << " = " << getRealParameterValue(i - 1, individual_parameter_size, parameters_max_values[i - 1], parameters_min_values[i - 1]) << "\n";
    }
    std::cout << "Function value = " << fitness << std::endl;
}