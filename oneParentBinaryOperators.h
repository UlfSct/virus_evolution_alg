#include "config.h"

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