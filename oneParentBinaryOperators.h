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
 * Функция выполняет фаргментарную инверсию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает инверсированную особь
 */
std::vector<bool> fragmentInversion(std::vector<bool> parent);

/**
 * Функция выполняет многопозиционную инверсию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает инверсированную особь
 */
std::vector<bool> multipositionInversion(std::vector<bool> parent);
