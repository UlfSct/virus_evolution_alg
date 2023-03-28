#include "oneParentBinaryOperators.h"

/**
 * Функция выполняет базовый кроссовер
 *
 * @param firstParent - первая родительская особь
 * @param secondParent -вторая родительская особь
 *
 * @return Возвращает две дочерние особи
 */
std::vector<std::vector<bool>> basicCrossover(std::vector<bool> firstParent, std::vector<bool> secondParent);

/**
 * Функция выполняет многопозиционный кроссовер
 *
 * @param firstParent - первая родительская особь
 * @param secondParent -вторая родительская особь
 *
 * @return Возвращает две дочерние особи
 */
std::vector<std::vector<bool>> multipositionCrossover(std::vector<bool> firstParent, std::vector<bool> secondParent);

/**
 * Функция выполняет однородный кроссовер
 *
 * @param firstParent - первая родительская особь
 * @param secondParent -вторая родительская особь
 *
 * @return Возвращает две дочерние особи
 */
std::vector<std::vector<bool>> homogeneousCrossover(std::vector<bool> firstParent, std::vector<bool> secondParent);

/**
 * Функция выполняет шаблонный кроссовер
 *
 * @param firstParent - первая родительская особь
 * @param secondParent -вторая родительская особь
 * @param pattern - шаблон
 *
 * @return Возвращает две дочерние особи
 */
std::vector<std::vector<bool>> templateCrossover(std::vector<bool> firstParent, std::vector<bool> secondParent, std::vector<bool> pattern);