#include "oneParentBinaryOperators.h"

std::vector<bool> basicMutation(std::vector<bool> parent)
{
    if (parent.size() == 0)
    {
        std::cout << "Размер вектора равен нулю";
        exit(1);
    }
    int geneNumber = rand() % (parent.size() - 1);
    parent.at(geneNumber) = parent.at(geneNumber);

    return parent;
}