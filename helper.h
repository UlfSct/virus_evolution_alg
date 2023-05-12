#include "Virus.h"


/**
 * Функция генерации популяции
 * 
 * @param population - вектор популяции
 * @param individual_parameter_size - размер булевого значения параметра
 * @param parameters_amount - количество параметров функции
 * @param population_size - размер популяции
 * @param parameters_min_values - минимальные значения параметров
 * @param parameters_max_values - максимальные значения параметров
*/
void generatePopulation
(
    std::vector<Virus*> &population,
    const int individual_parameter_size,
    const int parameters_amount,
    const int population_size,
    const double parameters_min_values[PARAMETERS_AMOUNT],
    const double parameters_max_values[PARAMETERS_AMOUNT]
);

/**
 * Функция перемещения вокруг оси
 *
 * @param population - вектор популяции
 * @param low - начало отрезка сортировки
 * @param high - конец отрезка сортировки
 * @param finding_min - булева константа минимазация или максимизация
 *
 * @returns - индекс обена элемента
 */
int partition(std::vector<Virus*> &population, int low, int high, const bool finding_min);

/**
 * Функция быстрой сортировки
 *
 * @param population - вектор популяции
 * @param low - начало отрезка сортировки
 * @param high - конец отрезка сортировки
 * @param finding_min - булева константа минимазация или максимизация
 */
void quickSort(std::vector<Virus *> &population, int low, int high, bool finding_min);

/**
 * Функция сортировки популяции по значению функции приспособленности
 * 
 * @param population - вектор популяции
 * @param finding_min - вектор популяции
 * @param strain_amount - вектор популяции
*/
void sortPopulationByFitness(std::vector<Virus *> &population, bool finding_min, const int strain_amount);

/**
 * Функция расчитывает расстояние хэмминга
 *
 * @param elite - вектор элитной особи
 * @param strain - вектор штамма
 *
 * @return - Возвращает расстояние хэмминга для двух особей
 */
int differenceInHammingDistance(std::vector<bool> elite, std::vector<bool> strain);