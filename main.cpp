#include "evolutionStrategies.h"


float R(std::vector<float> x, const int parameters_amount) 
{
    float result = - (x[1] + 47) * std::sin(std::sqrt(std::abs(x[1] + x[0] / 2 + 47))) - x[0] * std::sin(std::sqrt(std::abs(x[1] - x[0] - 47)));
    return result;
}


class Virus
{
private:
    std::vector<bool> data;
    float fitness;
    int iterations_in_elite_group;
    int left_iterations_in_strain;
    bool is_strain;

    void updateFitnessValue
    (
        const int parameters_amount, 
        const int individual_parameter_size,
        const float parameters_min_values[PARAMETERS_AMOUNT], 
        const float parameters_max_values[PARAMETERS_AMOUNT]
    ) 
    {
        if (data.size() == 0) return;
        
        std::vector<float> x;

        for (int k = 0; k < parameters_amount; k++)
        {
            x.push_back(getRealParameterValue(k, individual_parameter_size, parameters_max_values[k], parameters_min_values[k]));
        }
        this->fitness = R(x, parameters_amount);
    }

    float getRealParameterValue(int k, const int individual_parameter_size, const float max_value, const float min_value)
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

public:
    Virus()
    {
        iterations_in_elite_group = 0;
        left_iterations_in_strain = 0;
        is_strain = false;
    }

    Virus
    (
        std::vector<bool> data,
        const int parameters_amount, 
        const int individual_parameter_size,
        const float parameters_min_values[PARAMETERS_AMOUNT], 
        const float parameters_max_values[PARAMETERS_AMOUNT]
    )
    {
        this->data = data;
        iterations_in_elite_group = 0;
        left_iterations_in_strain = 0;
        is_strain = false;
        
        updateFitnessValue(parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values);
    }

    ~Virus()
    {
        data.clear();
    }

    std::vector<bool> getData() 
    {
        return this->data;
    }

    float getFitness()
    {
        return this->fitness;
    }

    bool isStrain()
    {
        return is_strain;
    }

    void printResults
    (
        const int parameters_amount, 
        const int individual_parameter_size,
        const float parameters_min_values[PARAMETERS_AMOUNT], 
        const float parameters_max_values[PARAMETERS_AMOUNT]
    )
    {
        for (int i = 1; i <= parameters_amount; i++)
        {
            std::cout << "Optimized x" << i << " = " << getRealParameterValue(i - 1, individual_parameter_size, parameters_max_values[i - 1], parameters_min_values[i - 1]) << "\n";
        }
        std::cout << "Function value = " << fitness << std::endl;
        
    }
};



void generatePopulation
(
    std::vector<Virus*>& population, 
    const int individual_parameter_size, 
    const int parameters_amount, 
    const int population_size,
    const float parameters_min_values[PARAMETERS_AMOUNT],
    const float parameters_max_values[PARAMETERS_AMOUNT]
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




void sortPopulationByFitness(std::vector<Virus*>& population, bool finding_min)
{
    int population_size = population.size();

	for (int i = 0; i < population_size; i++)
	{
        float min_value = population[i]->getFitness();
        int min_i = i;
		for (int j = i; j < population_size; j++)
        {
            if (finding_min)
            {
                if (min_value > population[j]->getFitness())
                {
                    min_value = population[j]->getFitness();
                    min_i = j;
                }
            }
            else
            {
                if (min_value < population[j]->getFitness())
                {
                    min_value = population[j]->getFitness();
                    min_i = j;
                }
            }
        }
            
        std::swap(population[i], population[min_i]);
	}

}


void mutateVirusOneParent(std::vector<bool> data, std::vector<std::vector<bool>>& new_viruses)
{
    int mutation_index = rand() % 7;

    switch (mutation_index)
    {
    case 0:
        new_viruses.push_back(translocation(data));
        break;
    case 1:
        new_viruses.push_back(basicMutation(data));
        break;
    case 2:
        new_viruses.push_back(basicInversion(data));
        break;
    case 3:
        new_viruses.push_back(multipositionMutation(data));
        break;
    case 4:
        new_viruses.push_back(duplication(data));
        break;
    case 5:
        new_viruses.push_back(fragmentInversion(data));
        break;
    case 6:
        new_viruses.push_back(multipositionInversion(data));
        break;
    default:
        break;
    }
}


void virusAlgorithm
(
    const int elite_group_size, 
    const int population_size, 
    const int individual_parameter_size, 
    const int strain_min_hamming_difference,
    const int parameters_amount, 
    const float parameters_min_values[PARAMETERS_AMOUNT], 
    const float parameters_max_values[PARAMETERS_AMOUNT],
    const bool finding_min, 
    const int max_empty_steps, 
    const int max_steps, 
    const int iterations_for_strain
)
{
    std::vector<Virus*> population;
    generatePopulation(population, individual_parameter_size, parameters_amount, population_size, parameters_min_values, parameters_max_values);
    sortPopulationByFitness(population, finding_min);

    int empty_steps = 0;
    int current_step = 1;
    float optimized_value = population[0]->getFitness();

    while (empty_steps < max_empty_steps && current_step <= max_steps)
    {
        std::cout << "Current step:" << current_step << "\n";

        std::cout << "Elite\n"; 
        for (int i = 0; i < elite_group_size; i++)
        {
            population.push_back(new Virus(population[i]->getData(), parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
            std::vector<std::vector<bool>> new_viruses;
            mutateVirusOneParent(population[i]->getData(), new_viruses);
            for (auto new_virus : new_viruses)
            {
                population.push_back(new Virus(new_virus, parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
            }
        }

        std::cout << "Basic\n"; 
        for (int i = elite_group_size; i < population_size; i++)
        {
            population.push_back(new Virus(population[i]->getData(), parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
        }

        std::cout << "Sort 1\n"; 
        sortPopulationByFitness(population, finding_min);


        std::cout << "Last chance " << population.size() << "\n"; 
        int current_population_size = population.size();
        for (int i = population_size; i < current_population_size; i++)
        {
            std::vector<std::vector<bool>> new_viruses;
            mutateVirusOneParent(population[i]->getData(), new_viruses);
            std::cout << i << " ";
            for (auto new_virus : new_viruses)
            {
                population.push_back(new Virus(new_virus, parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
            }
        }

        std::cout << "\nSort 2\n"; 
        sortPopulationByFitness(population, finding_min);

        int population_size = population.size();

        std::cout << "Deleting\n"; 
        for (int i = population_size - 1; i >= 0; i++)
        {
            if (population.size() <= POPULATION_SIZE) break;

            population.pop_back();
        }
        
        current_step++;

        if (finding_min)
        {
            if (population[0]->getFitness() < optimized_value) optimized_value = population[0]->getFitness();
            else empty_steps++;
        }
        else
        {
            if (population[0]->getFitness() > optimized_value) optimized_value = population[0]->getFitness();
            else empty_steps++;
        }
    }
    

    if (empty_steps >= max_empty_steps)
    {
        std::cout << "MAX_EMPTY_STEPS_EXCEED\n";
    }

    if (current_step >= max_steps)
    {
        std::cout << "MAX_STEPS_EXCEED\n";
    }

    population[0]->printResults(parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values);
}


int main()
{
    srand(time(0));
    virusAlgorithm
    (
        ELITE_GROUP_SIZE, 
        POPULATION_SIZE, 
        INDIVIDUAL_PARAMETER_SIZE, 
        STRAIN_MIN_HAMMING_DIFFERENCE, 
        PARAMETERS_AMOUNT, 
        PARAMETERS_MIN_VALUES, 
        PARAMETERS_MAX_VALUES,
        FINDING_MIN,
        MAX_EMPTY_STEPS,
        MAX_STEPS,
        ITERATIONS_FOR_STRAIN
    );
    return 0;
}
