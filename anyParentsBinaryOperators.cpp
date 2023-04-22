#include "anyParentsBinaryOperators.h"

std::vector<bool> segregation(std::vector<std::vector<bool>> parents)
{
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

std::vector<std::vector<bool>> multichromosomalCrossover(std::vector<std::vector<bool>> parents)
{
    if (parents.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    std::vector<std::vector<bool>> daughter;
    std::vector<std::vector<int>> daughterComposition;
    std::vector<int> dividingPositions;
    for (int divisionIndex = 0; divisionIndex < parents.size() - 1;)
    {
        bool usedValue = false;
        int divisionPosition = 1 + rand() % (parents.at(0).size() - 1);
        for (auto el : dividingPositions)
        {
            if (el == divisionPosition)
            {
                usedValue = true;
                break;
            }
        }
        if (!usedValue)
        {
            dividingPositions.push_back(divisionPosition);
            divisionIndex++;
        }
    }
    sort(dividingPositions.begin(), dividingPositions.end());
    dividingPositions.push_back(parents.at(0).size());
    int numberIndividuals = 1;
    for (int i = 2; i <= parents.size(); i++)
    {
        numberIndividuals = numberIndividuals * i;
    }
    int numberDaughterIndividuals = 0;
    while (numberDaughterIndividuals != numberIndividuals)
    {
        int numberFirstFragment = numberDaughterIndividuals / (numberIndividuals / parents.size());
        std::vector<bool> daughterIndividuals;
        for (int geneIndex = 0; geneIndex < dividingPositions.at(0); geneIndex++)
        {
            daughterIndividuals.push_back(parents.at(numberFirstFragment).at(geneIndex));
        }
        std::vector<int> usedParents;
        usedParents.clear();
        usedParents.push_back(numberFirstFragment);
        bool newDaughter = true;
        while (newDaughter)
        {
            for (int indexFragment = 1; indexFragment < parents.size();)
            {
                bool usedValue = false;
                int indexParents = rand() % parents.size();
                for (int usedIndexParents = 0; usedIndexParents < usedParents.size(); usedIndexParents++)
                {
                    if (usedParents.at(usedIndexParents) == indexParents)
                    {
                        usedValue = true;
                        break;
                    }
                }
                if (!usedValue)
                {
                    usedParents.push_back(indexParents);
                    for (int geneIndex = dividingPositions.at(indexFragment - 1); geneIndex < parents.at(0).size(); geneIndex++)
                    {
                        if (indexFragment != parents.size())
                        {
                            if (geneIndex == dividingPositions.at(indexFragment))
                            {
                                break;
                            }
                        }
                        daughterIndividuals.push_back(parents.at(indexParents).at(geneIndex));
                    }
                    indexFragment++;
                }
            }
            for (int i = 0; i < daughterComposition.size(); i++)
            {
                if (daughterComposition.at(i) == usedParents)
                {
                    newDaughter = false;
                    break;
                }
            }
            if (newDaughter)
            {
                daughterComposition.push_back(usedParents);
                daughter.push_back(daughterIndividuals);
                numberDaughterIndividuals++;
                newDaughter = false;
            }
        }
        if (numberDaughterIndividuals == 100)
        {
            break;
        }
    }

    return daughter;
}