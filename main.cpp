#include <iostream>

#include "Processor.h"

int main()
{
    std::string filename;
    DistT dist;

    std::cout << "filename: ";
    std::cin >> filename;

    std::cout << "distance: ";
    std::cin >> dist;

    Processor processor(filename, dist);
    processor.clusterize();

    return 0;
}