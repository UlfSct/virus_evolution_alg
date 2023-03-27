#include "oneParentBinaryOperators.h"

std::vector<bool> translocation(std::vector<bool> parent)
{
    std::cout << "Translocation operator" << std::endl;
    srand(time(NULL));
    if (parent.size() == 0)
    {
        std::cout << "Error: Vector is empty" << std::endl;
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

    for (int i = 0; i < tmpParent.size(); i++)
    {
        std::cout << tmpParent[i] << " ";
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

std::vector<std::vector<bool>> selectiveMutation(std::vector<bool> parent)
{
    std::cout << "selectiveMutation";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    int mutationCount = 2 + rand() % (parent.size() - 1);
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

std::vector<bool> duplication(std::vector<bool> parent)
{
    std::cout << "duplication";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    std::vector<bool> duplicatedParent;
    duplicatedParent = parent;
    while (duplicatedParent == parent)
    {
        int copySize = 0;
        int copyStartPosition = rand() % duplicatedParent.size();
        if (copyStartPosition == duplicatedParent.size() - 1)
        {
            copySize = 1;
        }
        else
        {
            while (copySize < 1)
            {
                copySize = rand() % duplicatedParent.size() - copyStartPosition;
            }
        }
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
    }
    return duplicatedParent;
}

std::vector<bool> fragmentInversion(std::vector<bool> parent)
{
    std::cout << "fragmentInversion";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    std::vector<bool> invertedParent;
    int firstStartPosition = rand() % (parent.size() - 1);
    int firstFragmentSize = 0;
    while (firstFragmentSize < 1)
    {
        firstFragmentSize = rand() % parent.size() - firstStartPosition;
    }
    int secondStartPosition;
    int secondFragmentSize = 0;
    do
    {
        do
        {
            secondStartPosition = rand() % (parent.size() - 1);
        } while (secondStartPosition >= firstStartPosition && secondStartPosition < firstStartPosition + firstFragmentSize);
        do
        {
            secondFragmentSize = rand() % parent.size() - secondStartPosition;
        } while ((secondStartPosition + secondFragmentSize >= firstStartPosition && secondStartPosition + secondFragmentSize <= firstStartPosition + firstFragmentSize) || secondFragmentSize < 1);
    } while ((secondStartPosition < firstStartPosition + firstFragmentSize) && (secondStartPosition + secondFragmentSize > firstStartPosition));
    if (secondStartPosition < firstStartPosition)
    {
        int copyVariable = firstStartPosition;
        firstStartPosition = secondStartPosition;
        secondStartPosition = copyVariable;
        copyVariable = firstFragmentSize;
        firstFragmentSize = secondFragmentSize;
        secondFragmentSize = copyVariable;
    }
    for (int copyIndex = 0; copyIndex < firstStartPosition; copyIndex++)
    {
        invertedParent.push_back(parent.at(copyIndex));
    }
    for (int copyIndex = secondStartPosition; copyIndex < secondStartPosition + secondFragmentSize; copyIndex++)
    {
        invertedParent.push_back(parent.at(copyIndex));
    }
    for (int copyIndex = firstStartPosition + firstFragmentSize; copyIndex < secondStartPosition; copyIndex++)
    {
        invertedParent.push_back(parent.at(copyIndex));
    }
    for (int copyIndex = firstStartPosition; copyIndex < firstStartPosition + firstFragmentSize; copyIndex++)
    {
        invertedParent.push_back(parent.at(copyIndex));
    }
    for (int copyIndex = secondStartPosition + secondFragmentSize; copyIndex < parent.size(); copyIndex++)
    {
        invertedParent.push_back(parent.at(copyIndex));
    }

    return invertedParent;
}

std::vector<bool> multipositionInversion(std::vector<bool> parent)
{
    std::cout << "multipositionInversion";
    if (parent.size() == 0)
    {
        std::cout << "The size of the vector is zero";
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
    std::vector<std::vector<bool>> parentFragments(divisionCount + 1);
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

    return invertedParent;
}
