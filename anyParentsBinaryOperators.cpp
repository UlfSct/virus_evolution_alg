#include "anyParentsBinaryOperators.h"

std::vector<bool> segregation(std::vector<std::vector<bool>> parents)
{
    std::cout << "segregation";
    if (parents.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    std::vector<bool> daughter;
    int maxSize = parents.at(0).size();
    int sizeFragment;
    int startFragment;
    for (int parentIndex = 0; parentIndex < parents.size() - 1; parentIndex++)
    {
        startFragment = rand() % parents.at(0).size();
        do
        {
            sizeFragment = startFragment + rand() % (maxSize - (parents.size() - parentIndex - 1)) - startFragment;
        } while ((parents.at(parentIndex).size() < startFragment + sizeFragment) || (sizeFragment == 0));
        for (int geneIndex = startFragment; geneIndex < startFragment + sizeFragment; geneIndex++)
        {
            daughter.push_back(parents.at(parentIndex).at(geneIndex));
        }
        maxSize -= sizeFragment;
    }
    do
    {
        startFragment = rand() % (parents.at(0).size() - maxSize + 1);
    } while (parents.at(0).size() - maxSize < startFragment);
    for (int geneIndex = startFragment; geneIndex < startFragment + maxSize; geneIndex++)
    {
        daughter.push_back(parents.at(parents.size() - 1).at(geneIndex));
    }

    return daughter;
}