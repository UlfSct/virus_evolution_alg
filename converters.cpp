#include "converters.h"

std::vector<bool> bytesToGrey(std::vector<bool> data)
{
    std::vector<bool> grey;
    grey.push_back(0 ^ data.at(0));
    for (int geneIndex = 0; geneIndex < data.size() - 1; geneIndex++)
    {
        grey.push_back(data.at(geneIndex) ^ data.at(geneIndex + 1));
    }

    return grey;
}


std::vector<bool> greyToBytes(std::vector<bool> data)
{
    std::vector<bool> binary;
    binary.push_back(0 ^ data.at(0));
    for (int geneIndex = 0; geneIndex < data.size() - 1; geneIndex++)
    {
        binary.push_back(binary.at(geneIndex) ^ data.at(geneIndex + 1));
    }

    return binary;
}