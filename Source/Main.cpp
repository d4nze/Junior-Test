#include <iostream>

#include "ConfigurationDataReader.hpp"
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
    std::string configPath("Configuration.txt");
    
    if (auto pathError = PathValidator::generateErrorMessage(inputPath))
    {
        return exitWithError("Can't open input file. " + pathError.value());
    }
    if (auto pathError = PathValidator::generateErrorMessage(configPath))
    {
        return exitWithError("Can't open configuration file. " + pathError.value());
    }

    std::map<SymbolHolder, std::int32_t> symbolCounters;
    std::set<SymbolHolder> uniqueSymbols;
    std::vector<Predicate*> predicates;

    ConfigurationDataReader configDataReader(configPath, predicates, uniqueSymbols, symbolCounters);
    if (auto error = configDataReader.readData())
    {
        return exitWithError(error.value());
    }

    InputDataReader inputDataReader(inputPath, uniqueSymbols, symbolCounters);
    if (auto error = inputDataReader.readData())
    {
        return exitWithError(error.value());
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
