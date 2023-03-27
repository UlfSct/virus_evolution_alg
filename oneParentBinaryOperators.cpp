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

    for (int i = 0; i < tmpParent.size(); i++) {
        std::cout << tmpParent[i] << " ";
    }

    std::reverse(tmpParent.begin(), tmpParent.end());

    for (int geneParentPosition = genePositionFirst, geneTmpParentPosition = 0; geneTmpParentPosition < tmpParent.size(); geneParentPosition++, geneTmpParentPosition++)
    {
        parent[geneParentPosition] = tmpParent[geneTmpParentPosition];
    }

    return parent;
}
