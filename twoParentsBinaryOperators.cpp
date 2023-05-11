#include "twoParentsBinaryOperators.h"

std::vector<std::vector<bool>> basicCrossover(std::vector<bool> firstParent, std::vector<bool> secondParent)
{
    //std::cout << "basicCrossover\n";
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
    std::vector<std::vector<bool>> variantsDaughterSpecies(2);
    for (int geneIndex = 0; geneIndex < firstParent.size(); geneIndex++)
    {
        if (geneIndex < divisionPosition)
        {
            variantsDaughterSpecies.at(0).push_back(firstParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(secondParent.at(geneIndex));
        }
        else
        {
            variantsDaughterSpecies.at(0).push_back(secondParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(firstParent.at(geneIndex));
        }
    }

    return variantsDaughterSpecies;
}

std::vector<std::vector<bool>> multipositionCrossover(std::vector<bool> firstParent, std::vector<bool> secondParent)
{
    //std::cout << "multipositionCrossover\n";
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
    int divisionCount = 2 + rand() % (firstParent.size() - 2);
    std::vector<int> dividingPositions;
    for (int divisionIndex = 0; divisionIndex < divisionCount;)
    {
        bool usedValue = false;
        int divisionPosition = 1 + rand() % (firstParent.size() - 1);
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
    dividingPositions.push_back(firstParent.size()-1);
    std::vector<std::vector<bool>> variantsDaughterSpecies(2);
    int fragmentNumber = 0;
    for (int geneIndex = 0; geneIndex < firstParent.size(); geneIndex++)
    {
        if (geneIndex == dividingPositions.at(fragmentNumber))
        {
            fragmentNumber++;
        }
        if (fragmentNumber % 2 == 0)
        {
            variantsDaughterSpecies.at(0).push_back(firstParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(secondParent.at(geneIndex));
        }
        else
        {
            variantsDaughterSpecies.at(0).push_back(secondParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(firstParent.at(geneIndex));
        }
    }

    dividingPositions.clear();

    return variantsDaughterSpecies;
}

std::vector<std::vector<bool>> homogeneousCrossover(std::vector<bool> firstParent, std::vector<bool> secondParent)
{
    //std::cout << "homogeneousCrossover\n";
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
    std::vector<std::vector<bool>> variantsDaughterSpecies(2);
    std::vector<float> randomNumbers(firstParent.size());
    for (int geneIndex = 0; geneIndex < firstParent.size(); geneIndex++)
    {
        float randomValue = static_cast<float>(rand()) * static_cast<float>(1) / RAND_MAX;
        randomNumbers.at(geneIndex) = randomValue;
    }
    for (int geneIndex = 0; geneIndex < firstParent.size(); geneIndex++)
    {
        if (randomNumbers.at(geneIndex) >= thresholdValue)
        {
            variantsDaughterSpecies.at(0).push_back(firstParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(secondParent.at(geneIndex));
        }
        else
        {
            variantsDaughterSpecies.at(0).push_back(secondParent.at(geneIndex));
            variantsDaughterSpecies.at(1).push_back(firstParent.at(geneIndex));
        }
    }

    randomNumbers.clear();

    return variantsDaughterSpecies;
}
