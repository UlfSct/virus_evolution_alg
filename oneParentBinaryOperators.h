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
 * Функция выполняет селективную мутацию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает множество вариантов мутировших особей мутировшую особь
 */
std::vector<std::vector<bool>> selectiveMutation();

/**
 * Функция выполняет селективную инверсию
 *
 * @param parent -родительская особь
 *
 * @return Возвращает множество вариантов инверсированных особей
 */
std::vector<std::vector<bool>> selectiveInversion();

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
>>>>>>> 574f1f0867e5054229a08bdd4ff4d751370d9fb9
