#include "oneParentBinaryOperators.h"

std::vector<bool> basicMutation(std::vector<bool> parent)
{
    std::cout << "basicMutation";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    int geneNumber = rand() % parent.size();
    parent.at(geneNumber) = !parent.at(geneNumber);

    return parent;
}

std::vector<bool> basicInversion(std::vector<bool> parent)
{
    std::cout << "basicInversion";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
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
    std::cout << "multipositionMutation";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    int mutationCount = 2 + rand() % parent.size();
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
    std::cout << "selectiveMutation";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    int mutationCount = 2 + rand() % parent.size();
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

std::vector<std::vector<bool>> selectiveInversion(std::vector<bool> parent)
{
    std::cout << "selectiveInversion";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    int inversionCount = 2 + rand() % (parent.size() - 1);
    std::vector<bool> invertedIndividuals;
    invertedIndividuals = parent;
    std::vector<std::vector<bool>> variantsInvertedIndividuals(inversionCount, invertedIndividuals);
    std::vector<int> usedPosition;
    for (int inversionIndex = 0; inversionIndex < inversionCount;)
    {
        bool usedValue = false;
        int inversionPosition = 1 + rand() % (variantsInvertedIndividuals.at(inversionIndex).size() - 1);
        for (int inversionPositionIndex = 0; inversionPositionIndex < inversionIndex; inversionPositionIndex++)
        {
            if (usedPosition.at(inversionPositionIndex) == inversionPosition)
            {
                usedValue = true;
                break;
            }
        }

        if (!usedValue)
        {
            usedPosition.push_back(inversionPosition);

            std::copy(invertedIndividuals.begin() + inversionPosition, invertedIndividuals.end(), variantsInvertedIndividuals.at(inversionIndex).begin());
            std::copy(invertedIndividuals.begin(), invertedIndividuals.begin() + inversionPosition, variantsInvertedIndividuals.at(inversionIndex).begin() + variantsInvertedIndividuals.at(inversionIndex).size() - inversionPosition);

            inversionIndex++;
        }
    }

    return variantsInvertedIndividuals;
}