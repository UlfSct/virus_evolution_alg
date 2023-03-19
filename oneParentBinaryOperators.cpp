#include "oneParentBinaryOperators.h"

std::vector<bool> basicMutation(std::vector<bool> parent)
{
    if (parent.size() == 0)
    {
        std::cout << "Размер вектора равен нулю";
        exit(1);
    }
    int geneNumber = rand() % (parent.size() - 1);
    parent.at(geneNumber) = !parent.at(geneNumber);

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
    std::copy(parent.begin() + inversionPosition, parent.end(), invertedParent.begin());
    std::copy(parent.begin(), parent.begin() + inversionPosition, invertedParent.begin() + invertedParent.size() - inversionPosition);

    return invertedParent;
}

std::vector<bool> multipositionMutation(std::vector<bool> parent)
{
    if (parent.size() == 0)
    {
        std::cout << "Размер вектора равен нулю";
        exit(1);
    }
    int mutationCount = 1 + rand() % parent.size();
    std::vector<int> mutatedGenes;
    for (int mutationIndex = 0; mutationIndex < mutationCount;)
    {
        int geneNumber = rand() % parent.size();
        if (mutationIndex == 0)
        {
            mutatedGenes.push_back(geneNumber);
            parent.at(geneNumber) = !parent.at(geneNumber);
            mutationIndex++;
        }
        else
        {
            for (int mutatedGenesIndex = 0; mutatedGenesIndex < mutatedGenes.size(); mutatedGenesIndex++)
            {
                if (geneNumber == mutatedGenes.at(mutatedGenesIndex))
                {
                    break;
                }
                else
                {
                    if (mutatedGenesIndex == mutatedGenes.size() - 1)
                    {
                        mutatedGenes.push_back(geneNumber);
                        parent.at(geneNumber) = !parent.at(geneNumber);
                        mutationIndex++;
                    }
                }
            }
        }
    }

    return parent;
}