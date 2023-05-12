#include "twoParentsBinaryOperators.h"

void basicCrossover(std::vector<bool> &firstParent, std::vector<bool> &secondParent, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "basicCrossover\n";
    if ((firstParent.size() == 0) || (secondParent.size() == 0))
    {
        if ((firstParent.size() == 0) && (secondParent.size() == 0))
        {
            std::cout << "The size of both vectors is zero";
            exit(1);
        }
        else
        {
            if (firstParent.size() == 0)
            {
                std::cout << "The size of the first vector is zero";
                exit(1);
            }
            else
            {
                std::cout << "The size of the second vector is zero";
                exit(1);
            }
        }
    }
    int divisionPosition = 1 + rand() % firstParent.size();
    std::vector<bool> tmpFirstParent = bytesToGrey(firstParent);
    std::vector<bool> tmpSecondParent = bytesToGrey(secondParent);
    std::vector<std::vector<bool>> variantsDaughterSpecies(2);
    for (int geneIndex = 0; geneIndex < firstParent.size(); geneIndex++)
    {
        if (geneIndex < divisionPosition)
        {
            variantsDaughterSpecies.at(0).push_back(tmpFirstParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(tmpSecondParent.at(geneIndex));
        }
        else
        {
            variantsDaughterSpecies.at(0).push_back(tmpFirstParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(tmpSecondParent.at(geneIndex));
        }
    }

    tmpFirstParent.clear();
    tmpFirstParent.shrink_to_fit();
    tmpSecondParent.clear();
    tmpSecondParent.shrink_to_fit();
    for (int i = 0; i < variantsDaughterSpecies.size(); i++)
    {
        new_viruses.push_back(greyToBytes(variantsDaughterSpecies.at(i)));
    }
    for (int i = 0; i < variantsDaughterSpecies.size(); i++)
    {
        variantsDaughterSpecies.at(i).clear();
        variantsDaughterSpecies.at(i).shrink_to_fit();
    }
    variantsDaughterSpecies.clear();
    variantsDaughterSpecies.shrink_to_fit();
}

void multipositionCrossover(std::vector<bool> &firstParent, std::vector<bool> &secondParent, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "multipositionCrossover\n";
    if ((firstParent.size() == 0) || (secondParent.size() == 0))
    {
        if ((firstParent.size() == 0) && (secondParent.size() == 0))
        {
            std::cout << "The size of both vectors is zero";
            exit(1);
        }
        else
        {
            if (firstParent.size() == 0)
            {
                std::cout << "The size of the first vector is zero";
                exit(1);
            }
            else
            {
                std::cout << "The size of the second vector is zero";
                exit(1);
            }
        }
    }
    std::vector<bool> tmpFirstParent = bytesToGrey(firstParent);
    std::vector<bool> tmpSecondParent = bytesToGrey(secondParent);
    int divisionCount = 2 + rand() % (tmpFirstParent.size() - 2);
    std::vector<int> dividingPositions;
    for (int divisionIndex = 0; divisionIndex < divisionCount;)
    {
        bool usedValue = false;
        int divisionPosition = 1 + rand() % (tmpFirstParent.size() - 1);
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
    dividingPositions.pop_back();
    dividingPositions.push_back(tmpFirstParent.size() - 1);
    std::vector<std::vector<bool>> variantsDaughterSpecies(2);
    int fragmentNumber = 0;
    for (int geneIndex = 0; geneIndex < tmpFirstParent.size(); geneIndex++)
    {
        if (geneIndex == dividingPositions.at(fragmentNumber))
        {
            fragmentNumber++;
        }
        if (fragmentNumber % 2 == 0)
        {
            variantsDaughterSpecies.at(0).push_back(tmpFirstParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(tmpSecondParent.at(geneIndex));
        }
        else
        {
            variantsDaughterSpecies.at(0).push_back(tmpSecondParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(tmpFirstParent.at(geneIndex));
        }
    }

    tmpFirstParent.clear();
    tmpFirstParent.shrink_to_fit();
    tmpSecondParent.clear();
    tmpSecondParent.shrink_to_fit();
    dividingPositions.clear();
    dividingPositions.shrink_to_fit();
    for (int i = 0; i < variantsDaughterSpecies.size(); i++)
    {
        new_viruses.push_back(greyToBytes(variantsDaughterSpecies.at(i)));
    }
    for (int i = 0; i < variantsDaughterSpecies.size(); i++)
    {
        variantsDaughterSpecies.at(i).clear();
        variantsDaughterSpecies.at(i).shrink_to_fit();
    }
    variantsDaughterSpecies.clear();
    variantsDaughterSpecies.shrink_to_fit();
}

void homogeneousCrossover(std::vector<bool> &firstParent, std::vector<bool> &secondParent, std::vector<std::vector<bool>> &new_viruses)
{
    // std::cout << "homogeneousCrossover\n";
    if ((firstParent.size() == 0) || (secondParent.size() == 0))
    {
        if ((firstParent.size() == 0) && (secondParent.size() == 0))
        {
            std::cout << "The size of both vectors is zero";
            exit(1);
        }
        else
        {
            if (firstParent.size() == 0)
            {
                std::cout << "The size of the first vector is zero";
                exit(1);
            }
            else
            {
                std::cout << "The size of the second vector is zero";
                exit(1);
            }
        }
    }
    float thresholdValue = 0.7;
    std::vector<bool> tmpFirstParent = bytesToGrey(firstParent);
    std::vector<bool> tmpSecondParent = bytesToGrey(secondParent);
    std::vector<std::vector<bool>> variantsDaughterSpecies(2);
    std::vector<float> randomNumbers(tmpFirstParent.size());
    for (int geneIndex = 0; geneIndex < tmpFirstParent.size(); geneIndex++)
    {
        float randomValue = static_cast<float>(rand()) * static_cast<float>(1) / RAND_MAX;
        randomNumbers.at(geneIndex) = randomValue;
    }
    for (int geneIndex = 0; geneIndex < tmpFirstParent.size(); geneIndex++)
    {
        if (randomNumbers.at(geneIndex) >= thresholdValue)
        {
            variantsDaughterSpecies.at(0).push_back(tmpFirstParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(tmpSecondParent.at(geneIndex));
        }
        else
        {
            variantsDaughterSpecies.at(0).push_back(tmpSecondParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(tmpFirstParent.at(geneIndex));
        }
    }
    
    tmpFirstParent.clear();
    tmpFirstParent.shrink_to_fit();
    tmpSecondParent.clear();
    tmpSecondParent.shrink_to_fit();
    randomNumbers.clear();
    randomNumbers.shrink_to_fit();
    for (int i = 0; i < variantsDaughterSpecies.size(); i++)
    {
        new_viruses.push_back(greyToBytes(variantsDaughterSpecies.at(i)));
    }
    for (int i = 0; i < variantsDaughterSpecies.size(); i++)
    {
        variantsDaughterSpecies.at(i).clear();
        variantsDaughterSpecies.at(i).shrink_to_fit();
    }
    variantsDaughterSpecies.clear();
    variantsDaughterSpecies.shrink_to_fit();
}
