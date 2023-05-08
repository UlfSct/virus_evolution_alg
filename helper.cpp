#include "helper.h"


void generatePopulation
(
    std::vector<Virus*> &population,
    const int individual_parameter_size,
    const int parameters_amount,
    const int population_size,
    const double parameters_min_values[PARAMETERS_AMOUNT],
    const double parameters_max_values[PARAMETERS_AMOUNT]
)
{
    for (int i = 0; i < population_size; i++)
    {
        std::vector<bool> data;

        for (int j = 0; j < individual_parameter_size * parameters_amount; j++)
        {
            data.push_back(rand() % 2);
        }

        population.push_back(new Virus(data, parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
    }
}


int partition(std::vector<Virus *> &population, int low, int high, const bool finding_min)
{
    double pivot = population[low]->getFitness();
    int i = low - 1;
    int j = high + 1;
    if (finding_min)
    {
        while (1)
        {
            do
            {
                i++;
            } while (population[i]->getFitness() < pivot);

            do
            {
                j--;
            } while (population[j]->getFitness() > pivot);

            if (i >= j)
            {
                return j;
            }

            std::swap(population[i], population[j]);
        }
    }
    else
    {
        while (1)
        {
            do
            {
                i++;
            } while (population[i]->getFitness() > pivot);

            do
            {
                j--;
            } while (population[j]->getFitness() < pivot);

            if (i >= j)
            {
                return j;
            }

            std::swap(population[i], population[j]);
        }
    }
}


void quickSort(std::vector<Virus *> &population, int low, int high, bool finding_min)
{
    if (low >= high)
    {
        return;
    }

    double pivot = partition(population, low, high, finding_min);

    quickSort(population, low, pivot, finding_min);

    quickSort(population, pivot + 1, high, finding_min);
}


void sortPopulationByFitness(std::vector<Virus *> &population, bool finding_min, const int strain_amount)
{

    int population_size = population.size();

    for (int i = 0; i < population_size; i++)
    {
        int min_i = 0;
        if (population[i]->isStrain())
        {
            std::swap(population[i], population[min_i]);
        }
    }
    if (strain_amount >= 2)
    {
        quickSort(population, 0, strain_amount - 1, finding_min);
    }

    quickSort(population, strain_amount, population_size - 1, finding_min);
}


std::vector<bool> bytesToGrey(std::vector<bool> data)
{
    std::vector<bool> grey;
    grey.push_back(0 ^ data.at(0));
    for (int geneIndex = 0; geneIndex < data.size() - 1; geneIndex++)
    {
        grey.push_back(data.at(geneIndex) ^ data.at(geneIndex + 1));
    }

    return grey;
}


std::vector<bool> greyToBytes(std::vector<bool> data)
{
    std::vector<bool> binary;
    binary.push_back(0 ^ data.at(0));
    for (int geneIndex = 0; geneIndex < data.size() - 1; geneIndex++)
    {
        binary.push_back(binary.at(geneIndex) ^ data.at(geneIndex + 1));
    }

    return binary;
}


int differenceInHammingDistance(std::vector<bool> elite, std::vector<bool> strain)
{
    int distance = 0;
    for (int geneIndex = 0; geneIndex < elite.size(); geneIndex++)
    {
        if (elite[geneIndex] != strain[geneIndex])
        {
            distance++;
        }
    }

    return distance;
}