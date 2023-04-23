#include "config.h"

/*
 * Функция выполняет операцию транслокации
 *
 * @param parent -родительская особь
 *
 * @return Возвращает мутировшую особь
 */
std::vector<bool> translocation(std::vector<bool> parent);

/**
 * Функция выполняет базовую мутацию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает мутировшую особь
 */
std::vector<bool> basicMutation(std::vector<bool> parent);

/**
 * Функция выполняет базовую инверсию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает инверсированную особь
 */
std::vector<bool> basicInversion(std::vector<bool> parent);

/**
 * Функция выполняет многопозиционную мутацию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает мутировшую особь
 */
std::vector<bool> multipositionMutation(std::vector<bool> parent);

/**
 * Функция выполняет дупликацию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает особь после дупликации
 */
std::vector<bool> duplication(std::vector<bool> parent);

/**
 * Функция выполняет многопозиционную инверсию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает инверсированную особь
 */
std::vector<bool> multipositionInversion(std::vector<bool> parent);

/**
 * Функция выполняет селективную мутацию
 *
 * @param parent -родительская особь
 * @param max_daughter_amount -максимальное количетсво дочерних особей
 *
 * @return Возвращает множество вариантов мутировших особей
 */
std::vector<std::vector<bool>> selectiveMutation(std::vector<bool> parent, const int max_daughter_amount);

/**
 * Функция выполняет селективную инверсию
 *
 * @param parent -родительская особь
 * @param max_daughter_amount -максимальное количетсво дочерних особей
 *
 * @return Возвращает множество вариантов инверсированных особей
 */
std::vector<std::vector<bool>> selectiveInversion(std::vector<bool> parent, const int max_daughter_amount);