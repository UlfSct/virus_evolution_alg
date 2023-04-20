#include "includes.h"


// размер элитки
const int ELITE_GROUP_SIZE = 10;

// размер популяции
const int POPULATION_SIZE = 50;

// размер параметра
const int INDIVIDUAL_PARAMETER_SIZE = 30;

// минимальная разница в расстоянии хэмминга между штаммами
const int STRAIN_MIN_HAMMING_DIFFERENCE = 3;

// количество параметров функции
const int PARAMETERS_AMOUNT = 2;

// минимальные значения параметров
const float PARAMETERS_MIN_VALUES[PARAMETERS_AMOUNT] = { -512.0, -512.0 };

// минимальные значения параметров
const float PARAMETERS_MAX_VALUES[PARAMETERS_AMOUNT] = { 512.0, 512.0 };

// булева константа минимазация или максимизация
const bool FINDING_MIN = true;

// Константа максимального количества пустых шагов
const int MAX_EMPTY_STEPS = 200;

// Константа максимального количества шагов
const int MAX_STEPS = 10000;

// Количество итераций, чтобы вирус из элитки стал штаммом
const int ITERATIONS_FOR_STRAIN = 30;

// Количество итераций, чтобы вирус из штамма стал никем
const int ITERATIONS_IN_STRAIN = 30;

