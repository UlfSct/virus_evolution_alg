#include "evolutionStrategies.h"

double R(std::vector<double> x, const int parameters_amount)
{
    double result = -(x[1] + 47) * std::sin(std::sqrt(std::abs(x[1] + x[0] / 2 + 47))) - x[0] * std::sin(std::sqrt(std::abs(x[1] - x[0] - 47)));
    return result;
}

class Virus
{
private:
    std::vector<bool> data;
    double fitness;
    int iterations_in_elite_group;
    int left_iterations_in_strain;
    bool is_strain;

    void updateFitnessValue(
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

    double getRealParameterValue(int k, const int individual_parameter_size, const double max_value, const double min_value)
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
        iterations_in_elite_group = -1;
        left_iterations_in_strain = -1;
        is_strain = false;
    }

    Virus(
        std::vector<bool> data,
        const int parameters_amount,
        const int individual_parameter_size,
        const double parameters_min_values[PARAMETERS_AMOUNT],
        const double parameters_max_values[PARAMETERS_AMOUNT])
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

    double getFitness()
    {
        return this->fitness;
    }

    bool isStrain()
    {
        return is_strain;
    }

    void iterationInEliteGroup()
    {
        this->iterations_in_elite_group++;
    }

    void iterationInStrain()
    {
        this->left_iterations_in_strain++;
    }

    int getIterationInElite()
    {
        return this->iterations_in_elite_group;
    }

    int getIterationInStrain()
    {
        return this->left_iterations_in_strain;
    }

    void strainStatusChange()
    {
        this->is_strain = !(this->is_strain);
        this->left_iterations_in_strain = 0;
    }

    void zeroingIterations()
    {
        this->left_iterations_in_strain = 0;
        this->iterations_in_elite_group = 0;
    }

    void printResults(
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
};

void generatePopulation(
    std::vector<Virus *> &population,
    const int individual_parameter_size,
    const int parameters_amount,
    const int population_size,
    const double parameters_min_values[PARAMETERS_AMOUNT],
    const double parameters_max_values[PARAMETERS_AMOUNT])
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

/**
 * Функция выполняет перемещение вокруг оси
 *
 * @param population - вектор популяции
 * @param low - начало отрезка сортировки
 * @param high - конец отрезка сортировки
 * @param finding_min - булева константа минимазация или максимизация
 *
 */
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

/**
 * Функция выполняет быструю сортировку
 *
 * @param population - вектор популяции
 * @param low - начало отрезка сортировки
 * @param high - конец отрезка сортировки
 * @param finding_min - булева константа минимазация или максимизация
 *
 */
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

/**
 * Функция выполняет перевод из двоичного кода в код Грея
 *
 * @param data - вектор особи в двоичном представление
 *
 * @return Возвращает вектор особи в коде Грея
 */
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

/**
 * Функция выполняет перевод из кода Грея в двоичный код
 *
 * @param data - вектор особи в коде Грея
 *
 * @return Возвращает вектор особи в двоичном представление
 */
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

/**
 * Функция расчитывает расстояние хэмминга
 *
 * @param elite - вектор элитной особи
 * @param strain - вектор штамма
 *
 * @return Возвращает расстояние хэмминга для двух особей
 */
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

void mutateVirus(std::vector<bool> data,
                 std::vector<Virus *> &population,
                 std::vector<std::vector<bool>> &new_viruses,
                 int empty_steps, const int max_empty_steps,
                 const int max_daughter_amount)
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

void virusAlgorithm(
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
    const int max_daughter_amount)
{
    std::vector<Virus *> population;
    int strain_amount = 0;
    generatePopulation(population, individual_parameter_size, parameters_amount, population_size, parameters_min_values, parameters_max_values);
    sortPopulationByFitness(population, finding_min, strain_amount);
    int empty_steps = 0;
    int current_step = 1;
    double optimized_value = population[0]->getFitness();
    while (empty_steps < max_empty_steps && current_step <= max_steps)
    {
        std::cout << "Current step:" << current_step << "\n";

        std::cout << "Elite\n";
        for (int i = strain_amount; i < strain_amount + elite_group_size; i++)
        {
            population.push_back(new Virus(population[i]->getData(), parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
            population[i]->iterationInEliteGroup();
            std::vector<std::vector<bool>> new_viruses;
            mutateVirus(population[i]->getData(), population, new_viruses, empty_steps, max_empty_steps, max_daughter_amount);
            for (auto new_virus : new_viruses)
            {
                population.push_back(new Virus(new_virus, parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
            }
        }

        std::cout << "Basic\n";
        for (int i = strain_amount + elite_group_size; i < population_size; i++)
        {
            population.push_back(new Virus(population[i]->getData(), parameters_amount, individual_parameter_size, parameters_min_values, parameters_max_values));
        }

        std::cout << "Sort 1\n";
        sortPopulationByFitness(population, finding_min, strain_amount);

        std::cout << "Last chance " << population.size() << "\n";
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

        std::cout << "\nSort 2\n";
        sortPopulationByFitness(population, finding_min, strain_amount);

        int population_size = population.size();

        std::cout << "Deleting\n";
        for (int i = population_size - 1; i >= 0; i++)
        {
            if (population.size() <= POPULATION_SIZE)
                break;

            population.pop_back();
        }
        std::cout << "Strain\n";
        int current_strain_amount = strain_amount;
        for (int i = 0; i < current_strain_amount; i++)
        {
            population[i]->iterationInStrain();

            if (population[i]->getIterationInStrain() >= iterations_in_strains)
            {
                population[i]->strainStatusChange();
                strain_amount--;
            }
        }
        if (strain_amount < max_strain_amount)
        {
            for (int i = strain_amount; i < strain_amount + elite_group_size; i++)
            {
                if (strain_amount < max_strain_amount && population[i]->getIterationInElite() >= iterations_for_strain)
                {
                    bool normalDistance = true;
                    for (int j = 0; j < strain_amount; j++)
                    {
                        if (differenceInHammingDistance(population[i]->getData(), population[j]->getData()) < strain_min_hamming_difference)
                            normalDistance = false;
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
