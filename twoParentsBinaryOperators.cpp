#include "twoParentsBinaryOperators.h"

std::vector<std::vector<bool>> basicCrossover(std::vector<bool> firstParent, std::vector<bool> secondParent)
{
    std::cout << "basicCrossover";
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
