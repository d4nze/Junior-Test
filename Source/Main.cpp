#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <set>

#include "InputDataReader.hpp"
#include "PathValidator.hpp"
#include "PredicateFactory.hpp"
#include "PredicateValidator.hpp"

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
    std::map<SymbolHolder, std::int32_t> symbolCounters;
    std::set<SymbolHolder> uniqueSymbols;
    std::vector<Predicate*> predicates;

    if (!configFile.is_open())
    {
        return exitWithError("Can't open predicates file.");
    }
    if (configFile.eof())
    {
        return exitWithError("Configuration file is empty.");
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
        uniqueSymbols.insert(symbolHolder);

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

    InputDataReader inputDataReader(inputPath, uniqueSymbols, symbolCounters);
    if (auto error = inputDataReader.readData())
    {
        return exitSuccessfully(error.value());
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
