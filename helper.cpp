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


void sortPopulationByFitness(std::vector<Virus *> &population, bool finding_min, int strain_amount)
{

    int population_size = population.size();
    
    for (int i = 0; i < population_size; i++)
    {
        int min_i = 0;
        if (population[i]->isStrain())
        {
            if(i == min_i) continue;
            std::swap(population[i], population[min_i]);
            min_i++;
        }
    }

    if (strain_amount >= 2)
    {
        quickSort(population, 0, strain_amount - 1, finding_min);
    }

    quickSort(population, strain_amount, population_size - 1, finding_min);
    

    /*for (int i = 0; i < population_size - 1; i++)
    {
        if (population[i]->isStrain()) continue;
        double opt_fitness = population[i]->getFitness();
        int opt_index = i;

        bool wasnt_broken = true;

        for (int j = i; j < population_size; j++)
        {
            if (population[j]->isStrain())
            {
                std::swap(population[j], population[i]);
                wasnt_broken = false;
                break;
            }

            double current_fitness = population[j]->getFitness();

            if (finding_min && current_fitness < opt_fitness || !finding_min && current_fitness > opt_fitness)
            {
                opt_index = j;
                opt_fitness = current_fitness;
            }
        }

        if (wasnt_broken && i != opt_index)
        {
            std::swap(population[i], population[opt_index]);
        }
    }*/
}



int differenceInHammingDistance(std::vector<bool> elite, std::vector<bool> strain)
{
    int distance = 0;

    for (int geneIndex = 0; geneIndex < elite.size(); geneIndex++)
    {
        if (elite[geneIndex] != strain[geneIndex]) distance++;
    }

    return distance;
}