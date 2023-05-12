#include "converters.h"

/*
 * Функция выполняет операцию транслокации
 *
 * @param parent -родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 * @return Возвращает мутировшую особь
 */
void translocation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет базовую мутацию
 *
 * @param parent -родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 */
void basicMutation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет базовую инверсию
 *
 * @param parent -родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 */
void basicInversion(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет многопозиционную мутацию
 *
 * @param parent -родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 */
void multipositionMutation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет дупликацию
 *
 * @param parent -родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 */
void duplication(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет многопозиционную инверсию
 *
 * @param parent -родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 */
void multipositionInversion(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет селективную мутацию
 *
 * @param parent -родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 */
void selectiveMutation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);

/**
 * Функция выполняет селективную инверсию
 *
 * @param parent -родительская особь
 * @param new_viruses - вектор вывода новых особей
 *
 */
void selectiveInversion(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses);