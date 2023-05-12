#include "includes.h"

// размер элитки
const int ELITE_GROUP_SIZE = 400;

// размер популяции
const int POPULATION_SIZE = 1000;

// размер параметра
const int INDIVIDUAL_PARAMETER_SIZE = 15;

// минимальная разница в расстоянии хэмминга между штаммами
const int STRAIN_MIN_HAMMING_DIFFERENCE = 3;

// количество параметров функции
const int PARAMETERS_AMOUNT = 2;

// минимальные значения параметров
const double PARAMETERS_MIN_VALUES[PARAMETERS_AMOUNT] = {-512.0, -512.0};

// минимальные значения параметров
const double PARAMETERS_MAX_VALUES[PARAMETERS_AMOUNT] = {512.0, 512.0};

// булева константа минимазация или максимизация
const bool FINDING_MIN = true;

// Константа максимального количества пустых шагов
const int MAX_EMPTY_STEPS = 50;

// Константа максимального количества шагов
const int MAX_STEPS = 500;

// Количество итераций, чтобы вирус из элитки стал штаммом
const int ITERATIONS_FOR_STRAIN = 10;

// Количество итераций, чтобы вирус из штамма стал никем
const int ITERATIONS_IN_STRAIN = 10;

// Константа максимального количества штаммов
const int MAX_STRAIN_AMOUNT = 100;//120

// Константа максимального количества родительских особей
const int MAX_PARENT_AMOUNT = 6;//5

// Константа максимально количества дочерних особей
const int MAX_DAUGHTER_AMOUNT = 50;

// Константа кратности количества операций для штаммов
const double STRAIN_OPERATIONS_RATIO = 3;

// Константа идеального значения функции
const double PERFECT_FUNCTION_VALUE = -959.6407;

// Необходимая точность значения
const double E = 0.5;