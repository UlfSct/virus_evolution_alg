#include "converters.h"

/*
 * Функция выполняет операцию транслокации
 *
 * @param parent -родительская особь
 *
 * @return Возвращает мутировшую особь
 */
void translocation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет базовую мутацию
 *
 * @param parent -родительская особь
 *
 */
void basicMutation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет базовую инверсию
 *
 * @param parent -родительская особь
 *
 */
void basicInversion(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет многопозиционную мутацию
 *
 * @param parent -родительская особь
 *
 */
void multipositionMutation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет дупликацию
 *
 * @param parent -родительская особь
 *
 */
void duplication(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет многопозиционную инверсию
 *
 * @param parent -родительская особь
 *
 */
void multipositionInversion(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет селективную мутацию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает множество вариантов мутировших особей
 */
void selectiveMutation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет селективную инверсию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает множество вариантов инверсированных особей
 */
void selectiveInversion(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);