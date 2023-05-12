#include "oneParentBinaryOperators.h"

void translocation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses)
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

    std::vector<bool> greyParent = bytesToGrey(parent);
    std::vector<bool> tmpParent;

    for (int genePosition = genePositionFirst; genePosition <= genePositionLast; genePosition++)
    {
        tmpParent.push_back(greyParent[genePosition]);
    }

    std::reverse(tmpParent.begin(), tmpParent.end());

    for (int geneParentPosition = genePositionFirst, geneTmpParentPosition = 0; geneTmpParentPosition < tmpParent.size(); geneParentPosition++, geneTmpParentPosition++)
    {
        greyParent[geneParentPosition] = tmpParent[geneTmpParentPosition];
    }

    tmpParent.clear();
    tmpParent.shrink_to_fit();
    new_viruses.push_back(greyToBytes(greyParent));
    greyParent.clear();
    greyParent.shrink_to_fit();
}

void basicMutation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "basicMutation\n";
    std::vector<bool> tmpParent = bytesToGrey(parent);
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero\n";
        exit(1);
    }
    int geneNumber = rand() % tmpParent.size();
    tmpParent.at(geneNumber) = !tmpParent.at(geneNumber);

    new_viruses.push_back(greyToBytes(tmpParent));
    tmpParent.clear();
    tmpParent.shrink_to_fit();
}

void basicInversion(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "basicInversion\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero\n";
        exit(1);
    }
    std::vector<bool> tmpParent = greyToBytes(parent);
    std::vector<bool> invertedParent(tmpParent.size());
    int inversionPosition = 1 + rand() % (tmpParent.size() - 1);
    std::copy(tmpParent.begin() + inversionPosition, tmpParent.end(), invertedParent.begin());
    std::copy(tmpParent.begin(), tmpParent.begin() + inversionPosition, invertedParent.begin() + invertedParent.size() - inversionPosition);

    new_viruses.push_back(greyToBytes(invertedParent));
    tmpParent.clear();
    tmpParent.shrink_to_fit();
    invertedParent.clear();
    invertedParent.shrink_to_fit();
}

void multipositionMutation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "multipositionMutation\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero\n";
        exit(1);
    }
    int mutationCount = 2 + rand() % (parent.size() - 1);
    std::vector<int> mutatedGenes;
    std::vector<bool> tmpParent = bytesToGrey(parent);
    for (int mutationIndex = 0; mutationIndex < mutationCount;)
    {
        bool usedValue = false;
        int geneNumber = rand() % tmpParent.size();

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
            tmpParent.at(geneNumber) = !tmpParent.at(geneNumber);
            mutationIndex++;
        }
    }

    mutatedGenes.clear();
    mutatedGenes.shrink_to_fit();
    new_viruses.push_back(greyToBytes(tmpParent));
    tmpParent.clear();
    tmpParent.shrink_to_fit();
}

void duplication(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "duplication\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero\n";
        exit(1);
    }
    std::vector<bool> duplicatedParent;
    duplicatedParent = bytesToGrey(parent);
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

    copyGenes.clear();
    copyGenes.shrink_to_fit();
    new_viruses.push_back(greyToBytes(duplicatedParent));
    duplicatedParent.clear();
    duplicatedParent.shrink_to_fit();
}

void multipositionInversion(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "multipositionInversion\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero\n";
        exit(1);
    }
    std::vector<bool> invertedParent;
    std::vector<bool> tmpParent = bytesToGrey(parent);
    int divisionCount = 2 + rand() % (parent.size() - 2);
    std::vector<int> dividingPositions;
    for (int divisionIndex = 0; divisionIndex < divisionCount;)
    {
        bool usedValue = false;
        int inversionPosition = 1 + rand() % (tmpParent.size() - 1);
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

    std::vector<std::vector<bool>> parentFragments(divisionCount + 1);
    int geneIndex = 0;
    for (int fragmentIndex = 0; fragmentIndex < divisionCount; fragmentIndex++)
    {
        for (geneIndex; geneIndex < dividingPositions.at(fragmentIndex); geneIndex++)
        {
            parentFragments.at(fragmentIndex).push_back(tmpParent.at(geneIndex));
        }
    }
    for (geneIndex; geneIndex < tmpParent.size(); geneIndex++)
    {
        parentFragments.at(parentFragments.size() - 1).push_back(tmpParent.at(geneIndex));
    }
    while (invertedParent.size() != tmpParent.size())
    {
        int fragmentIndex = rand() % parentFragments.size();
        invertedParent.insert(invertedParent.end(), parentFragments.at(fragmentIndex).begin(), parentFragments.at(fragmentIndex).end());
        parentFragments.at(fragmentIndex).clear();
        parentFragments.at(fragmentIndex) = parentFragments.at(parentFragments.size() - 1);
        parentFragments.resize(parentFragments.size() - 1);
    }
    numberAttempts++;

    dividingPositions.clear();
    dividingPositions.shrink_to_fit();
    parentFragments.clear();
    parentFragments.shrink_to_fit();
    tmpParent.clear();
    tmpParent.shrink_to_fit();
    new_viruses.push_back(greyToBytes(invertedParent));
    invertedParent.clear();
    invertedParent.shrink_to_fit();
}

void selectiveMutation(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "selectiveMutation\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    int mutationCount = 2 + rand() % 10;
    std::vector<std::vector<bool>> variantsMutatedIndividuals(mutationCount, bytesToGrey(parent));
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

    mutatedGenes.clear();
    mutatedGenes.shrink_to_fit();
    for (int mutationIndex = 0; mutationIndex < mutationCount; mutationIndex++)
    {
        new_viruses.push_back(greyToBytes(variantsMutatedIndividuals.at(mutationIndex)));
    }
    for (int i = 0; i < variantsMutatedIndividuals.size(); i++)
    {
        variantsMutatedIndividuals.at(i).clear();
        variantsMutatedIndividuals.at(i).shrink_to_fit();
    }
    variantsMutatedIndividuals.clear();
    variantsMutatedIndividuals.shrink_to_fit();
}

void selectiveInversion(std::vector<bool> &parent, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "selectiveInversion\n";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    int inversionCount = 2 + rand() % 10;
    std::vector<bool> invertedIndividuals;
    invertedIndividuals = bytesToGrey(parent);
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

    invertedIndividuals.clear();
    invertedIndividuals.shrink_to_fit();
    usedPosition.clear();
    usedPosition.shrink_to_fit();
    for (int inversionIndex = 0; inversionIndex < inversionCount; inversionIndex++)
    {
        new_viruses.push_back(greyToBytes(variantsInvertedIndividuals.at(inversionIndex)));
    }
    for (int i = 0; i < variantsInvertedIndividuals.size(); i++)
    {
        variantsInvertedIndividuals.at(i).clear();
        variantsInvertedIndividuals.at(i).shrink_to_fit();
    }
    variantsInvertedIndividuals.clear();
    variantsInvertedIndividuals.shrink_to_fit();
}