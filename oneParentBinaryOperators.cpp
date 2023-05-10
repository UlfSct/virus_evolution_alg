#include "oneParentBinaryOperators.h"

std::vector<bool> translocation(std::vector<bool> parent)
{
    // std::cout << "translocation\n";
    srand(time(NULL));
    if (parent.size() == 0)
    {
        std::cout << "Error: Vector is empty\n";
        exit(1);
    }

    int genePositionFirst, genePositionLast;

    do
    {
        genePositionFirst = rand() % parent.size() - 1;
        genePositionLast = rand() % parent.size();

    } while (genePositionFirst > genePositionLast || genePositionFirst <= 0 || genePositionFirst == genePositionLast);

    std::vector<bool> tmpParent;

    for (int genePosition = genePositionFirst; genePosition <= genePositionLast; genePosition++)
    {
        tmpParent.push_back(parent[genePosition]);
    }

    std::reverse(tmpParent.begin(), tmpParent.end());

    for (int geneParentPosition = genePositionFirst, geneTmpParentPosition = 0; geneTmpParentPosition < tmpParent.size(); geneParentPosition++, geneTmpParentPosition++)
    {
        parent[geneParentPosition] = tmpParent[geneTmpParentPosition];
    }

    return parent;
}

std::vector<bool> basicMutation(std::vector<bool> parent)
{
    // std::cout << "basicMutation\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero\n";
        exit(1);
    }
    int geneNumber = rand() % parent.size();
    parent.at(geneNumber) = !parent.at(geneNumber);

    return parent;
}

std::vector<bool> basicInversion(std::vector<bool> parent)
{
    // std::cout << "basicInversion\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero\n";
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
    // std::cout << "multipositionMutation\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero\n";
        exit(1);
    }
    int mutationCount = 2 + rand() % (parent.size() - 1);
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

std::vector<bool> duplication(std::vector<bool> parent)
{
    // std::cout << "duplication\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero\n";
        exit(1);
    }
    std::vector<bool> duplicatedParent;
    duplicatedParent = parent;
    int copySize = 0;
    int copyStartPosition = rand() % duplicatedParent.size();
    copySize = 1 + rand() % (duplicatedParent.size() - 1);
    int insertStartPosition = copyStartPosition;
    while (copyStartPosition == insertStartPosition)
    {
        insertStartPosition = rand() % duplicatedParent.size();
    }
    while (insertStartPosition + copySize > duplicatedParent.size())
    {
        copySize--;
    }
    std::vector<bool> copyGenes(copySize);
    std::copy(duplicatedParent.begin() + copyStartPosition, duplicatedParent.begin() + copyStartPosition + copySize, copyGenes.begin());

    for (int copyGenesIndex = 0; copyGenesIndex < copyGenes.size(); copyGenesIndex++)
    {
        duplicatedParent.at(insertStartPosition + copyGenesIndex) = copyGenes.at(copyGenesIndex);
    }
    return duplicatedParent;
}

std::vector<bool> multipositionInversion(std::vector<bool> parent)
{
    // std::cout << "multipositionInversion\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero\n";
        exit(1);
    }
    std::vector<bool> invertedParent;
    int divisionCount = 2 + rand() % (parent.size() - 2);
    std::vector<int> dividingPositions;
    for (int divisionIndex = 0; divisionIndex < divisionCount;)
    {
        bool usedValue = false;
        int inversionPosition = 1 + rand() % (parent.size() - 1);
        for (int inversionPositionIndex = 0; inversionPositionIndex < divisionIndex; inversionPositionIndex++)
        {
            if (dividingPositions.at(inversionPositionIndex) == inversionPosition)
            {
                usedValue = true;
                break;
            }
        }
        if (!usedValue)
        {
            dividingPositions.push_back(inversionPosition);
            divisionIndex++;
        }
    }
    sort(dividingPositions.begin(), dividingPositions.end());
    int numberAttempts = 0;
    do
    {
        std::vector<std::vector<bool>> parentFragments(divisionCount + 1);
        for (int fragmentIndex = 0; fragmentIndex < parentFragments.size(); fragmentIndex++)
        {
            parentFragments.at(fragmentIndex).clear();
        }
        invertedParent.clear();
        int geneIndex = 0;
        for (int fragmentIndex = 0; fragmentIndex < divisionCount; fragmentIndex++)
        {
            for (geneIndex; geneIndex < dividingPositions.at(fragmentIndex); geneIndex++)
            {
                parentFragments.at(fragmentIndex).push_back(parent.at(geneIndex));
            }
        }
        for (geneIndex; geneIndex < parent.size(); geneIndex++)
        {
            parentFragments.at(parentFragments.size() - 1).push_back(parent.at(geneIndex));
        }
        while (invertedParent.size() != parent.size())
        {
            int fragmentIndex = rand() % parentFragments.size();
            invertedParent.insert(invertedParent.end(), parentFragments.at(fragmentIndex).begin(), parentFragments.at(fragmentIndex).end());
            parentFragments.at(fragmentIndex).clear();
            parentFragments.at(fragmentIndex) = parentFragments.at(parentFragments.size() - 1);
            parentFragments.resize(parentFragments.size() - 1);
        }
        numberAttempts++;
    } while (invertedParent == parent || numberAttempts == 100);

    return invertedParent;
}

std::vector<std::vector<bool>> selectiveMutation(std::vector<bool> parent, const int max_daughter_amount)
{
    // std::cout << "selectiveMutation\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    int mutationCount = 2 + rand() % max_daughter_amount;
    if (mutationCount > 10)
        mutationCount = 10;
    std::vector<std::vector<bool>> variantsMutatedIndividuals(mutationCount, parent);
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

std::vector<std::vector<bool>> selectiveInversion(std::vector<bool> parent, const int max_daughter_amount)
{
    // std::cout << "selectiveInversion\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    int inversionCount = 2 + rand() % max_daughter_amount;
    if (inversionCount > 10)
        inversionCount = 10;
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