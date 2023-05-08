#include "RFunction.h"

/**
 * Класс вируса
*/
class Virus
{
private:
    std::vector<bool> data;
    double fitness;
    int iterations_in_elite_group;
    int iterations_in_strain;
    bool is_strain;

    /**
     * Функция обновления значения приспособленности
    */
    void updateFitnessValue
    (
        const int parameters_amount,
        const int individual_parameter_size,
        const double parameters_min_values[PARAMETERS_AMOUNT],
        const double parameters_max_values[PARAMETERS_AMOUNT]
    );

    /**
     * Вспомогательная функция взятия реального значения k-го параметра
    */
    double getRealParameterValue(int k, const int individual_parameter_size, const double max_value, const double min_value);

public:
    /**
     * Пустой конструктор класса Вирус
    */
    Virus();

    /**
     * Конструктор класса Вирус
    */
    Virus
    (
        std::vector<bool> data,
        const int parameters_amount,
        const int individual_parameter_size,
        const double parameters_min_values[PARAMETERS_AMOUNT],
        const double parameters_max_values[PARAMETERS_AMOUNT]
    );

    /**
     * Деструктор класса Вирус
    */
    ~Virus();

    /**
     * Функция получения значения поля data
    */
    std::vector<bool> getData();

    /**
     * Функция получения значения поля fitness
    */
    double getFitness();

    /**
     * Функция получения значения поля is_strain
    */
    bool isStrain();

    /**
     * Функция увеличения количества итераций в элитной группе на единицу
    */
    void increaseIterationsInEliteGroup();

    /**
     * Функция увеличения количества итераций в штамм-группе на единицу
    */
    void increaseIterationsInStrain();

    /**
     * Функция получения значения поля iterations_in_elite_group
    */
    int getIterationsInElite();

    /**
     * Функция получения значения поля iterations_in_strain
    */
    int getIterationsInStrain();

    /**
     * Функция изменения статуса штамма
    */
    void strainStatusChange();

    /**
     * Функция зануления счётчиков итераций в различных состояних
    */
    void zeroingIterations();

    /**
     * Функция вывода результатов оптимизации
    */
    void printResults(
        const int parameters_amount,
        const int individual_parameter_size,
        const double parameters_min_values[PARAMETERS_AMOUNT],
        const double parameters_max_values[PARAMETERS_AMOUNT]
    );
};