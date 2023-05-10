#include "helper.h"


/**
 * Функция мутации вируса
 * 
 * @param data - мутирующая особь
 * @param population - ссылка на вектор популяции
 * @param new_viruses - вектор получившихся детей
 * @param empty_steps - текущее количество пустых шагов
 * @param max_empty_steps - максимально допустимое количество пустых шагов
 * @param max_daughter_amount - максимальное количество детей от одной мутации
*/
void mutateVirus
(
    std::vector<bool> data,
    std::vector<Virus *> &population,
    std::vector<std::vector<bool>> &new_viruses,
    int empty_steps, 
    const int max_empty_steps,
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
        //daughterSpecies = selectiveMutation(bytesToGrey(data), max_daughter_amount);
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
        //daughterSpecies = selectiveInversion(bytesToGrey(data), max_daughter_amount);
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


/**
 * Цикл алгоритма эволюции
*/
double virusAlgorithm
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
    const int max_daughter_amount,
    const double strain_operations_ratio
)
{
    // Создаём популяцию
    std::vector<Virus *> population;
    int strain_amount = 0;
    generatePopulation(population, individual_parameter_size, parameters_amount, population_size, parameters_min_values, parameters_max_values);
    sortPopulationByFitness(population, finding_min, strain_amount);

    //  задаём начальные данные и текущее лучшее значение функции приспособленности
    int empty_steps = 0;
    int current_step = 1;
    double optimized_value = population[0]->getFitness();
    int optimized_value_index = 0;

    // файл вывода технической информации
    std::ofstream tech_out;
    tech_out.open("logs/tech_out.txt");
    tech_out.close();

    // файл вывода промежусточных результатов
    std::ofstream result_out;
    result_out.open("logs/result_out.txt");
    result_out.close();

    // файл вывода популяции на каждой итерации
    std::ofstream population_out;
    population_out.open("logs/population_out.txt");
    population_out.close();

    while (empty_steps < max_empty_steps && current_step <= max_steps)
    {
        //  сортировка
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "====================================================================\n";
        tech_out << "Current step: " << current_step << "\n";
        tech_out << "Sort 1 " << population.size() << "\n";
        sortPopulationByFitness(population, finding_min, strain_amount);

        //  дублирование и мутация в штаммах
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "Strain " << population.size() << "\n";
        tech_out.close();

        for (int i = strain_amount; i < strain_amount + elite_group_size; i++)
        {
            for (int j = 0; j < strain_operations_ratio; j++)
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
        }

        //  дублирование и мутация элитной группы
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "Elite " << population.size() << "\n";
        tech_out.close();

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

        // Размножение обычных особей
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "Basic " << population.size() << "\n";
        tech_out.close();

        for (int i = strain_amount + elite_group_size; i < population_size; i++)
        {
            population.push_back(new Virus(population[i]->getData(), parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
        }

        // Сортировка особей по приспособленности
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "Sort 2 " << population.size() << "\n";
        tech_out.close();

        sortPopulationByFitness(population, finding_min, strain_amount);

        // Последний шанс
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "Last chance " << population.size() << "\n";
        tech_out.close();

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

        // Финальная сортировка
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "Sort 3 " << population.size() << "\n";
        tech_out.close();

        sortPopulationByFitness(population, finding_min, strain_amount);

        // Отсечение хвоста популяции
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "Deleting " << population.size() << "\n";
        tech_out.close();

        while (population.size() > population_size)
        {
            population.pop_back();
        }

        // Вывод популяции по результатам итерации
        population_out.open("logs/population_out.txt", std::ios::app);

        population_out << "\nStep " << current_step << "\n";

        for (int i = 0; i < (parameters_amount + 1) * 20 + 1; i++)
        {
            population_out << "-";
        }
        population_out << "\n";

        for (int i = 0; i < parameters_amount; i++)
        {
            std::string tmp_string = "x[" + std::to_string(i + 1) + "]";
            population_out << "|" << std::setw(19) << tmp_string;
        }
        population_out << "|" << std::setw(19) << "R" << "|\n";

        for (int i = 0; i < (parameters_amount + 1) * 20 + 1; i++)
        {
            population_out << "-";
        }
        population_out << "\n";

        for (int i = 0; i < population_size; i++)
        {
            for (int k = 0; k < parameters_amount; k++)
            {
                double value = population[i]->getRealParameterValue(k, individual_parameter_size, parameters_max_values[k], parameters_min_values[k]);
                population_out << "|" << std::setw(19) << std::to_string(value);
            }

            population_out << "|" << std::setw(19) << population[i]->getFitness() << "|\n";

            for (int j = 0; j < (parameters_amount + 1) * 20 + 1; j++)
            {
                population_out << "-";
            }
            population_out << "\n";
        }
        population_out.close();
        
        // Обновление оптимизированного значения
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "Finding opt. " << population.size() << "\n";
        tech_out.close();
        
        bool value_changed = false;
        for (int i = 0; i < strain_amount + 1; i++)
        {
            double fitness = population[i]->getFitness();
            if (finding_min && fitness < optimized_value || !finding_min && fitness > optimized_value)
            {
                value_changed = true;
                optimized_value = fitness;
                optimized_value_index = i;

                result_out.open("logs/result_out.txt", std::ios::app);
                result_out << "====================================================================\n";
                for (int k = 0; k < parameters_amount; k++)
                {
                    result_out << "x[" << k + 1 << "] = " <<
                        population[i]->getRealParameterValue(k, individual_parameter_size, parameters_max_values[k], parameters_min_values[k])
                        << "\n";
                }
                result_out << "R = " << std::to_string(optimized_value) << "\n";
                result_out.close();
            }
        }

        if (value_changed) empty_steps = 0;
        else empty_steps++;

        // обновление итераций и статуса виурсов
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "Update vir. " << population.size() << "\n";
        tech_out.close();

        int current_strain_amount = strain_amount;

        for (int i = current_strain_amount; i < current_strain_amount + elite_group_size; i++)
        {
            population[i]->increaseIterationsInEliteGroup();

            if (population[i]->getIterationsInElite() == iterations_for_strain)
            {
                if (strain_amount < max_strain_amount)
                {
                    bool is_worthy = true;

                    for (int j = 0; j < current_strain_amount; j++)
                    {
                        if (differenceInHammingDistance(population[i]->getData(), population[j]->getData()) 
                            < strain_min_hamming_difference)
                        {
                            is_worthy = false;
                            break;
                        }
                    }

                    if (is_worthy)
                    {
                        population[i]->strainStatusChange();
                        strain_amount++;
                    }
                }
            }
        }

        for (int i = 0; i < current_strain_amount; i++)
        {
            population[i]->increaseIterationsInStrain();

            if (population[i]->getIterationsInStrain() == iterations_in_strains)
            {
                population[i]->strainStatusChange();
                population[i]->zeroingIterations();
                strain_amount--;
            }
        }

        for (int i = current_strain_amount + elite_group_size; i < population_size; i++)
        {
            population[i]->zeroingIterations();
        }

        // новая итерация
        current_step++;
    }

    // Вывод сообщения о выходе за количество пустых шагов
    if (empty_steps >= max_empty_steps)
    {
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "MAX_EMPTY_STEPS_EXCEED\n";
    }

    // Вывод сообщение о выходе за макимальное количество шагов
    if (current_step >= max_steps)
    {
        tech_out.open("logs/tech_out.txt", std::ios::app);
        tech_out << "MAX_STEPS_EXCEED\n";
    }

    // Вывод результатов оптимизации
    population[optimized_value_index]->printResults(parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values);

    return optimized_value;
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
        MAX_DAUGHTER_AMOUNT,
        STRAIN_OPERATIONS_RATIO
    );
    return 0;
}
