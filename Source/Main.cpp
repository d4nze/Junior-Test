#include <iostream>
#include <fstream>

#include "PathValidator.hpp"
#include "PredicateValidator.hpp"
#include "SymbolHolder.hpp"

std::int32_t exitWithError(std::string_view errorMessage)
{
    std::cout << "An error occurred:\n";
    std::cout << errorMessage << '\n';
    std::system("pause");
    return 1;
}

std::int32_t main(std::int32_t argc, char* argv[])
{
    if (argc <= 1)
    {
        return exitWithError("No arguments provided");
    }
    std::string inputPath(argv[1]);
    PathValidator inputPathValidator(inputPath);
    if (!inputPathValidator.isValid())
    {
        return exitWithError("Can't open input file. " + inputPathValidator.getErrorMessage());
    }

    PathValidator configPathValidator("Configuration.txt");
    if (!configPathValidator.isValid())
    {
        return exitWithError("Can't open configuration file. " + configPathValidator.getErrorMessage());
    }

    std::ifstream configFile("Configuration.txt");
    if (!configFile.is_open())
    {
        return exitWithError("Can't open predicates file.");
    }
    std::string part;
    do
    {
        PredicateValidator predicateValidator(configFile);
        if (!predicateValidator.isValid())
        {
            return exitWithError(predicateValidator.getErrorMessage());
        }
        std::cout << "Instruction symbol: " << predicateValidator.getSymbol().getData();
        std::cout << " Predicate: " << predicateValidator.getPredicate();
        std::cout << " Count: " << predicateValidator.getCount() << '\n';
    }
    while (!configFile.eof() && configFile >> part && part == "&&");
    if (!configFile.eof())
    {
        return exitWithError("Expected '&&' or end of file.");
    }

    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open())
    {
        return exitWithError("Can't open input file.");
    }

    for (std::string line; std::getline(inputFile, line);)
    {
        for (std::size_t i = 0; i < line.size();)
        {
            std::size_t lenght = SymbolHolder::predictSymbolLenght(line[i]);
            if (lenght == 0 || i + lenght > line.size())
            {
                std::cout << "It broke" << '\n';
                break;
            }
            if (lenght == 1)
            {
                std::cout << "Singlechar symbol: " << line[i++] << '\n';
                continue;
            }
            SymbolHolder symbolHolder(line.substr(i, lenght));
            std::cout << "Multichar symbol: " << symbolHolder.getData() << '\n';
            i += lenght;
        }
    }
    
    std::system("pause");
    return 0;
}
