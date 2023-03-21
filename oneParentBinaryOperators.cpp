#include "oneParentBinaryOperators.h"

std::vector<bool> basicMutation(std::vector<bool> parent)
{
    if (parent.size() == 0)
    {
        std::cout << "Размер вектора равен нулю";
        exit(1);
    }
    int geneNumber = rand() % parent.size();
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
        bool usedValue = false;
        int geneNumber = rand() % parent.size();

        for (int mutatedGenesIndex = 0; mutatedGenesIndex < mutationIndex; mutatedGenesIndex++)
        {
            if (mutatedGenes.at(mutatedGenesIndex) == geneNumber)
            {
                usedValue = true;
                break;
            }
        }

        if (!usedValue)
        {
            mutatedGenes.push_back(geneNumber);
            parent.at(geneNumber) = !parent.at(geneNumber);
            mutationIndex++;
        }
    }

    return parent;
}

std::vector<std::vector<bool>> selectiveMutation(std::vector<bool> parent)
{
    if (parent.size() == 0)
    {
        std::cout << "Размер вектора равен нулю";
        exit(1);
    }
    int mutationCount = 1 + rand() % parent.size();
    std::vector<bool> mutatedIndividuals;
    mutatedIndividuals = parent;
    std::vector<std::vector<bool>> variantsMutatedIndividuals(mutationCount, mutatedIndividuals);
    std::vector<int> mutatedGenes;
    for (int mutationIndex = 0; mutationIndex < mutationCount;)
    {
        bool usedValue = false;
        int geneNumber = rand() % variantsMutatedIndividuals.at(mutationIndex).size();
        for (int mutatedGenesIndex = 0; mutatedGenesIndex < mutationIndex; mutatedGenesIndex++)
        {
            if (mutatedGenes.at(mutatedGenesIndex) == geneNumber)
            {
                usedValue = true;
                break;
            }
        }

        if (!usedValue)
        {
            mutatedGenes.push_back(geneNumber);
            variantsMutatedIndividuals.at(mutationIndex).at(geneNumber) = !variantsMutatedIndividuals.at(mutationIndex).at(geneNumber);
            mutationIndex++;
        }
    }

    return variantsMutatedIndividuals;
}