#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <set>

#include "PathValidator.hpp"
#include "PredicateFactory.hpp"
#include "PredicateValidator.hpp"
#include "SymbolHolder.hpp"

std::int32_t exitWithError(std::string_view errorMessage)
{
    std::cout << "An error occurred:\n";
    std::cout << errorMessage << '\n';
    std::system("pause");
    return 1;
}

std::int32_t exitSuccessfully(std::string_view successMessage)
{
    std::cout << successMessage << '\n';
    std::system("pause");
    return 0;
}

std::int32_t main(std::int32_t argc, char* argv[])
{
    if (argc <= 1)
    {
        return exitWithError("No arguments provided");
    }

    std::string inputPath(argv[1]);
    
    if (auto pathError = PathValidator::generateErrorMessage(inputPath))
    {
        return exitWithError("Can't open input file. " + pathError.value());
    }
    if (auto pathError = PathValidator::generateErrorMessage("Configuration.txt"))
    {
        return exitWithError("Can't open configuration file. " + pathError.value());
    }

    std::ifstream configFile("Configuration.txt");
    std::ifstream inputFile(inputPath);
    std::map<SymbolHolder, std::int32_t> symbolCounters;
    std::set<SymbolHolder> symbols;
    std::vector<Predicate*> predicates;

    if (!configFile.is_open())
    {
        return exitWithError("Can't open predicates file.");
    }
    if (configFile.eof())
    {
        return exitWithError("Configuration file is empty.");
    }
    if (!inputFile.is_open())
    {
        return exitWithError("Can't open input file.");
    }

    std::string part;
    do
    {
        PredicateValidator predicateValidator(configFile);
        if (!predicateValidator.isValid())
        {
            return exitWithError(predicateValidator.getErrorMessage());
        }

        const SymbolHolder& symbolHolder = predicateValidator.getSymbol();
        const std::string& sPredicate = predicateValidator.getPredicate();
        std::int32_t count = predicateValidator.getCount();

        symbolCounters[symbolHolder] = 0;
        symbols.insert(symbolHolder);

        if (Predicate* predicate = PredicateFactory::createPredicate(symbolHolder, count, sPredicate))
        {
            predicates.push_back(predicate);
        }
    }
    while (!configFile.eof() && configFile >> part && part == "&&");
    if (!configFile.eof())
    {
        return exitWithError("Expected '&&' or end of file.");
    }

    for (char symbolPart; inputFile >> symbolPart;)
    {
        if (symbolPart == '\n')
        {
            continue;
        }
        std::size_t lenght = SymbolHolder::predictSymbolLenght(symbolPart);
        if (lenght == 0)
        {
            return exitWithError("Unsupported character.");
        }
        std::string sSymbol(lenght, symbolPart);
        for (std::size_t i = 1; i < lenght; i++)
        {
            inputFile >> symbolPart;
            sSymbol[i] = symbolPart;
        }
        SymbolHolder symbolHolder(sSymbol);
        if (symbols.find(symbolHolder) != symbols.end())
        {
            symbolCounters[symbolHolder]++;
        }
    }

    for (Predicate* predicate : predicates)
    {
        if (!predicate->compare(symbolCounters.at(predicate->getSymbolHolder())))
        {
            return exitSuccessfully("File doesn't fit the policy");
        }
    }
    
    return exitSuccessfully("File does fit the policy");
}
