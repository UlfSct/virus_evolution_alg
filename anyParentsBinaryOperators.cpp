#include "anyParentsBinaryOperators.h"

void segregation(std::vector<std::vector<bool>> &parents, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "segregation\n";
    if (parents.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    std::vector<std::vector<bool>> tmpParents;
    for (int i = 0; i < parents.size(); i++)
    {
        tmpParents.push_back(bytesToGrey(parents.at(i)));
    }

    std::vector<bool> daughter;
    int maxSize = tmpParents.at(0).size();
    int sizeFragment;
    int startFragment;
    for (int parentIndex = 0; parentIndex < tmpParents.size() - 1; parentIndex++)
    {
        startFragment = rand() % tmpParents.at(0).size();
        do
        {
            sizeFragment = startFragment + rand() % (maxSize - (tmpParents.size() - parentIndex - 1)) - startFragment;
        } while ((tmpParents.at(parentIndex).size() < startFragment + sizeFragment) || (sizeFragment == 0));
        for (int geneIndex = startFragment; geneIndex < startFragment + sizeFragment; geneIndex++)
        {
            daughter.push_back(tmpParents.at(parentIndex).at(geneIndex));
        }
        maxSize -= sizeFragment;
    }
    do
    {
        startFragment = rand() % (tmpParents.at(0).size() - maxSize + 1);
    } while (tmpParents.at(0).size() - maxSize < startFragment);
    for (int geneIndex = startFragment; geneIndex < startFragment + maxSize; geneIndex++)
    {
        daughter.push_back(tmpParents.at(tmpParents.size() - 1).at(geneIndex));
    }

    new_viruses.push_back(greyToBytes(daughter));
    daughter.clear();
    daughter.shrink_to_fit();
    for (int i = 0; i < tmpParents.size(); i++)
    {
        tmpParents.at(i).clear();
        tmpParents.at(i).shrink_to_fit();
    }
    tmpParents.clear();
    tmpParents.shrink_to_fit();
}

void multichromosomalCrossover(std::vector<std::vector<bool>> &parents, const int max_daughter_amount, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "multichromosomalCrossover\n";
    if (parents.size() == 0)
    {
        std::cout << "The size of the vector is zero";
        exit(1);
    }
    std::vector<std::vector<bool>> daughter;
    std::vector<std::vector<int>> daughterComposition;
    std::vector<int> dividingPositions;
    std::vector<std::vector<bool>> tmpParents;
    for (int i = 0; i < parents.size(); i++)
    {
        tmpParents.push_back(bytesToGrey(parents.at(i)));
    }
    for (int divisionIndex = 0; divisionIndex < tmpParents.size() - 1;)
    {
        bool usedValue = false;
        int divisionPosition = 1 + rand() % (tmpParents.at(0).size() - 1);
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
    dividingPositions.push_back(tmpParents.at(0).size());
    int numberIndividuals = 1;
    for (int i = 2; i <= tmpParents.size(); i++)
    {
        numberIndividuals = numberIndividuals * i;
    }
    int numberDaughterIndividuals = 0;
    while (numberDaughterIndividuals != numberIndividuals)
    {
        int numberFirstFragment = numberDaughterIndividuals / (numberIndividuals / tmpParents.size());
        std::vector<bool> daughterIndividuals;
        for (int geneIndex = 0; geneIndex < dividingPositions.at(0); geneIndex++)
        {
            daughterIndividuals.push_back(tmpParents.at(numberFirstFragment).at(geneIndex));
        }
        std::vector<int> usedParents;
        usedParents.clear();
        usedParents.push_back(numberFirstFragment);
        bool newDaughter = true;
        while (newDaughter)
        {
            for (int indexFragment = 1; indexFragment < tmpParents.size();)
            {
                bool usedValue = false;
                int indexParents = rand() % tmpParents.size();
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
                    for (int geneIndex = dividingPositions.at(indexFragment - 1); geneIndex < tmpParents.at(0).size(); geneIndex++)
                    {
                        if (indexFragment != tmpParents.size())
                        {
                            if (geneIndex == dividingPositions.at(indexFragment))
                            {
                                break;
                            }
                        }
                        daughterIndividuals.push_back(tmpParents.at(indexParents).at(geneIndex));
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
        if (numberDaughterIndividuals == max_daughter_amount)
        {
            break;
        }
    }

    for (int i = 0; i < daughter.size(); i++)
    {
        new_viruses.push_back(greyToBytes(daughter.at(i)));
    }
    for (int i = 0; i < daughter.size(); i++)
    {
        daughter.at(i).clear();
        daughter.at(i).shrink_to_fit();
    }
    daughter.clear();
    daughter.shrink_to_fit();
        for (int i = 0; i < daughterComposition.size(); i++)
    {
        daughterComposition.at(i).clear();
        daughterComposition.at(i).shrink_to_fit();
    }
    daughterComposition.clear();
    daughterComposition.shrink_to_fit();
    dividingPositions.clear();
    dividingPositions.shrink_to_fit();
    for (int i = 0; i < tmpParents.size(); i++)
    {
        tmpParents.at(i).clear();
        tmpParents.at(i).shrink_to_fit();
    }
    tmpParents.clear();
    tmpParents.shrink_to_fit();
}