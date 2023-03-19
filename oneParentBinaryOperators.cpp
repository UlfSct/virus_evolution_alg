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

std::vector<bool> basicInversion(std::vector<bool> parent)
{
    if (parent.size() == 0)
    {
        std::cout << "Размер вектора равен нулю";
        exit(1);
    }
    std::vector<bool> invertedParent(parent.size());
    int inversionPosition = 1 + rand() % (parent.size() - 1);
    for (int i = inversionPosition; i < parent.size() - 1; i++)
    {
        invertedParent.at(i - inversionPosition) = parent.at(i);
    }
    for (int i = 0; i < inversionPosition; i++)
    {
        invertedParent.at(inversionPosition+1+i) = parent.at(i);
    }
    
}