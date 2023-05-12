#include "twoParentsBinaryOperators.h"

/**
 * Функция выполняет сегрегацию
 *
 * @param parents - вектор родительских особей
 *
 */
void segregation(std::vector<std::vector<bool>> &parents, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет многохромосомный кроссовер
 *
 * @param parents - вектор родительских особей
 * @param max_daughter_amount - максимальное количество дочерних особей
 *
 */
void multichromosomalCrossover(std::vector<std::vector<bool>> &parents, const int max_daughter_amount, std::vector<std::vector<bool>> &new_viruses);