#include "includes.h"

// размер элитки
const int ELITE_GROUP_SIZE = 1;

// размер популяции
const int POPULATION_SIZE = 10;

// размер параметра
const int INDIVIDUAL_PARAMETER_SIZE = 30;

// минимальная разница в расстоянии хэмминга между штаммами
const int STRAIN_MIN_HAMMING_DIFFERENCE = 3;

// количество параметров функции
const int PARAMETERS_AMOUNT = 2;

// минимальные значения параметров
const double PARAMETERS_MIN_VALUES[PARAMETERS_AMOUNT] = {0.0, 0.0};

// минимальные значения параметров
const double PARAMETERS_MAX_VALUES[PARAMETERS_AMOUNT] = {512.0, 512.0};

// булева константа минимазация или максимизация
const bool FINDING_MIN = true;

// Константа максимального количества пустых шагов
const int MAX_EMPTY_STEPS = 20000;

// Константа максимального количества шагов
const int MAX_STEPS = 1000;

// Количество итераций, чтобы вирус из элитки стал штаммом
const int ITERATIONS_FOR_STRAIN = 30;

// Количество итераций, чтобы вирус из штамма стал никем
const int ITERATIONS_IN_STRAIN = 30;

// Константа максимального количества штаммов
const int MAX_STRAIN_AMOUNT = 10;

// Константа максимального количества родительских особей
const int MAX_PARENT_AMOUNT = 6;

// Константа радиуса поиска вокруг штамма
const int STRAIN_DUPLICATION_RADIUS = 2;

// Константа шаг поиска вокруг штамма
const double STEP_IN_STRAIN_DUPLICATION_RADIUS = 0.1;

// Константа максимально количества дочерних особей
const int MAX_DAUGHTER_AMOUNT = 100;