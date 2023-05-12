#include "oneParentBinaryOperators.h"

/**
 * Функция выполняет базовый кроссовер
 *
 * @param firstParent - первая родительская особь
 * @param secondParent -вторая родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 */
void basicCrossover(std::vector<bool> &firstParent, std::vector<bool> &secondParent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет многопозиционный кроссовер
 *
 * @param firstParent - первая родительская особь
 * @param secondParent -вторая родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 */
void multipositionCrossover(std::vector<bool> &firstParent, std::vector<bool> &secondParent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет однородный кроссовер
 *
 * @param firstParent - первая родительская особь
 * @param secondParent -вторая родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 */
void homogeneousCrossover(std::vector<bool> &firstParent, std::vector<bool> &secondParent, std::vector<std::vector<bool>> &new_viruses);
