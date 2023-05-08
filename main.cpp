#include "helper.h"


void mutateVirus
(
    std::vector<bool> data,
    std::vector<Virus *> &population,
    std::vector<std::vector<bool>> &new_viruses,
    int empty_steps, const int max_empty_steps,
    const int max_daughter_amount
)
{
    double indexForSelect = 1 + double(rand()) * double(pow(14.0, 1.0 + double(empty_steps) / double(max_empty_steps))) / RAND_MAX;
    int mutationIndex;
    for (mutationIndex = 1; mutationIndex < 14; mutationIndex++)
    {
        if (pow(double(mutationIndex), 1.0 + double(empty_steps) / double(max_empty_steps)) < indexForSelect && indexForSelect < pow(double(mutationIndex + 1), 1.0 + double(empty_steps) / double(max_empty_steps)))
        {
            break;
        }
    }
    int parentAmount = (int)(2 + (MAX_PARENT_AMOUNT - 2) * double(empty_steps) / double(max_empty_steps));
    std::vector<std::vector<bool>> parents;
    std::vector<std::vector<bool>> daughterSpecies;
    switch (mutationIndex)
    {
    case 1:
        new_viruses.push_back(greyToBytes(basicMutation(bytesToGrey(data))));
        break;
    case 2:
        new_viruses.push_back(greyToBytes(translocation(bytesToGrey(data))));
        break;
    case 3:
        new_viruses.push_back(greyToBytes(multipositionMutation(bytesToGrey(data))));
        break;
    case 4:
        new_viruses.push_back(greyToBytes(basicInversion(bytesToGrey(data))));
        break;
    case 5:
        daughterSpecies = basicCrossover(bytesToGrey(data), bytesToGrey(population[0]->getData()));
        for (int indexDaughter = 0; indexDaughter < daughterSpecies.size(); indexDaughter++)
        {
            new_viruses.push_back(greyToBytes(daughterSpecies.at(indexDaughter)));
        }
        break;
    case 6:
        new_viruses.push_back(greyToBytes(duplication(bytesToGrey(data))));
        break;
    case 7:
        daughterSpecies = selectiveMutation(bytesToGrey(data), max_daughter_amount);
        for (int indexDaughter = 0; indexDaughter < daughterSpecies.size(); indexDaughter++)
        {
            new_viruses.push_back(greyToBytes(daughterSpecies.at(indexDaughter)));
        }
        break;
    case 8:
        new_viruses.push_back(greyToBytes(multipositionInversion(bytesToGrey(data))));
        break;
    case 9:
        parents.push_back(bytesToGrey(data));
        for (int indexParent = 0; indexParent < parentAmount - 1; indexParent++)
        {
            parents.push_back(bytesToGrey(population[indexParent]->getData()));
        }
        new_viruses.push_back(greyToBytes(segregation(parents)));
        break;
    case 10:
        daughterSpecies = homogeneousCrossover(bytesToGrey(data), bytesToGrey(population[0]->getData()));
        for (int indexDaughter = 0; indexDaughter < daughterSpecies.size(); indexDaughter++)
        {
            new_viruses.push_back(greyToBytes(daughterSpecies.at(indexDaughter)));
        }
        break;
    case 11:
        daughterSpecies = multipositionCrossover(bytesToGrey(data), bytesToGrey(population[0]->getData()));
        for (int indexDaughter = 0; indexDaughter < daughterSpecies.size(); indexDaughter++)
        {
            new_viruses.push_back(greyToBytes(daughterSpecies.at(indexDaughter)));
        }
        break;
    case 12:
        daughterSpecies = selectiveInversion(bytesToGrey(data), max_daughter_amount);
        for (int indexDaughter = 0; indexDaughter < daughterSpecies.size(); indexDaughter++)
        {
            new_viruses.push_back(greyToBytes(daughterSpecies.at(indexDaughter)));
        }
        break;
    case 13:
        parents.push_back(bytesToGrey(data));
        for (int indexParent = 0; indexParent < parentAmount - 1; indexParent++)
        {
            parents.push_back(bytesToGrey(population[indexParent]->getData()));
        }
        daughterSpecies = multichromosomalCrossover(parents, max_daughter_amount);
        for (int indexDaughter = 0; indexDaughter < daughterSpecies.size(); indexDaughter++)
        {
            new_viruses.push_back(greyToBytes(daughterSpecies.at(indexDaughter)));
        }
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
    const double parameters_min_values[PARAMETERS_AMOUNT],
    const double parameters_max_values[PARAMETERS_AMOUNT],
    const bool finding_min,
    const int max_empty_steps,
    const int max_steps,
    const int iterations_for_strain,
    const int iterations_in_strains,
    const int max_strain_amount,
    const int max_parent_amount,
    const int strain_duplication_radius,
    const double step_in_strain_duplication_radius,
    const int max_daughter_amount
)
{
    // Создаём популяцию, и сортируем её по приспособленности
    std::vector<Virus *> population;
    int strain_amount = 0;
    generatePopulation(population, individual_parameter_size, parameters_amount, population_size, parameters_min_values, parameters_max_values);
    sortPopulationByFitness(population, finding_min, strain_amount);

    //  задаём начальные данные и текущее лучшее значение функции приспособленности
    int empty_steps = 0;
    int current_step = 1;
    double optimized_value = population[0]->getFitness();

    // файл вывода технической информации
    std::ofstream tech_out;
    tech_out.open("logs/tech_out.txt");

    while (empty_steps < max_empty_steps && current_step <= max_steps)
    {
        tech_out << "Current step:" << current_step << "\n";

        tech_out << "Elite\n";
        for (int i = strain_amount; i < strain_amount + elite_group_size; i++)
        {
            population.push_back(new Virus(population[i]->getData(), parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
            population[i]->increaseIterationsInEliteGroup();
            std::vector<std::vector<bool>> new_viruses;
            mutateVirus(population[i]->getData(), population, new_viruses, empty_steps, max_empty_steps, max_daughter_amount);
            for (auto new_virus : new_viruses)
            {
                population.push_back(new Virus(new_virus, parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
            }
        }

        tech_out << "Basic\n";
        for (int i = strain_amount + elite_group_size; i < population_size; i++)
        {
            population.push_back(new Virus(population[i]->getData(), parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
        }

        tech_out << "Sort 1\n";
        sortPopulationByFitness(population, finding_min, strain_amount);

        tech_out << "Last chance " << population.size() << "\n";
        int current_population_size = population.size();
        for (int i = population_size; i < current_population_size; i++)
        {
            std::vector<std::vector<bool>> new_viruses;
            mutateVirus(population[i]->getData(), population, new_viruses, empty_steps, max_empty_steps, max_daughter_amount);
            for (auto new_virus : new_viruses)
            {
                population.push_back(new Virus(new_virus, parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
            }
        }

        tech_out << "\nSort 2\n";
        sortPopulationByFitness(population, finding_min, strain_amount);

        int population_size = population.size();

        tech_out << "Deleting\n";
        for (int i = population_size - 1; i >= 0; i++)
        {
            if (population.size() <= population_size) break;

            population.pop_back();
        }
        tech_out << "Strain\n";
        int current_strain_amount = strain_amount;
        for (int i = 0; i < current_strain_amount; i++)
        {
            population[i]->increaseIterationsInStrain();

            if (population[i]->getIterationsInStrain() >= iterations_in_strains)
            {
                population[i]->strainStatusChange();
                strain_amount--;
            }
        }
        if (strain_amount < max_strain_amount)
        {
            for (int i = strain_amount; i < strain_amount + elite_group_size; i++)
            {
                if (strain_amount < max_strain_amount && population[i]->getIterationsInElite() >= iterations_for_strain)
                {
                    bool normalDistance = true;
                    for (int j = 0; j < strain_amount; j++)
                    {
                        if (differenceInHammingDistance(population[i]->getData(), population[j]->getData()) < strain_min_hamming_difference)
                        {
                            normalDistance = false;
                        }
                    }
                    if (normalDistance)
                    {
                        population[i]->strainStatusChange();
                        strain_amount++;
                        population[i]->zeroingIterations();
                    }
                }
            }
        }

        current_step++;

        if (finding_min)
        {
            bool empty_step_check = true;
            for (int i = 0; i < strain_amount + 1; i++)
            {
                if (population[i]->getFitness() < optimized_value)
                {
                    optimized_value = population[i]->getFitness();
                    empty_step_check = false;
                }
            }
            if (empty_step_check)
            {
                empty_steps++;
            }
        }
        else
        {
            bool empty_step_check = true;
            for (int i = 0; i < strain_amount + 1; i++)
            {
                if (population[i]->getFitness() > optimized_value)
                {
                    optimized_value = population[i]->getFitness();
                    empty_step_check = false;
                }
            }
            if (empty_step_check)
            {
                empty_steps++;
            }
        }
    }

    // Вывод сообщения о выходе за количество пустых шагов
    if (empty_steps >= max_empty_steps)
    {
        tech_out << "MAX_EMPTY_STEPS_EXCEED\n";
    }

    // Вывод сообщение о выходе за макимальное количество шагов
    if (current_step >= max_steps)
    {
        tech_out << "MAX_STEPS_EXCEED\n";
    }

    // Вывод результатов оптимизации
    population[0]->printResults(parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values);
}

int main()
{
    srand(time(0));
    virusAlgorithm(
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
        ITERATIONS_FOR_STRAIN,
        ITERATIONS_IN_STRAIN,
        MAX_STRAIN_AMOUNT,
        MAX_PARENT_AMOUNT,
        STRAIN_DUPLICATION_RADIUS,
        STEP_IN_STRAIN_DUPLICATION_RADIUS,
        MAX_DAUGHTER_AMOUNT
        // процент сходимости
        // количество вызовов целевой функции
    );
    return 0;
}
