#include "config.h"

/**
 * Функция выполняет перевод из двоичного кода в код Грея
 *
 * @param data - вектор особи в двоичном представление
 *
 * @returns - Возвращает вектор особи в коде Грея
 */
std::vector<bool> bytesToGrey(std::vector<bool> data);

/**
 * Функция выполняет перевод из кода Грея в двоичный код
 *
 * @param data - вектор особи в коде Грея
 *
 * @returns - Возвращает вектор особи в двоичном представление
 */
std::vector<bool> greyToBytes(std::vector<bool> data);