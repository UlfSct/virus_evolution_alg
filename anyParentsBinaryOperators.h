#include "twoParentsBinaryOperators.h"

/**
 * Функция выполняет сегрегацию
 *
 * @param parents - вектор родительских особей
 *
 * @return Возвращает дочернюю особь
 */
std::vector<bool> segregation(std::vector<std::vector<bool>> parents);

/**
 * Функция выполняет многохромосомный кроссовер
 *
 * @param parents - вектор родительских особей
 * @param max_daughter_amount - максимальное количество дочерних особей
 *
 * @return Возвращает множество дочерних особей
 */
std::vector<std::vector<bool>> multichromosomalCrossover(std::vector<std::vector<bool>> parents, const int max_daughter_amount);