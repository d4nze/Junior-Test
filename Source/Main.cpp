#include <iostream>

#include "ConfigurationDataReader.hpp"
#include "InputDataReader.hpp"

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

    SymbolsHolder symbolsHolder;
    PredicatesHolder predicatesHolder;
    ConfigurationDataReader configDataReader("Configuration.txt", predicatesHolder, symbolsHolder);
    InputDataReader inputDataReader(argv[1], symbolsHolder);

    if (auto pathError = configDataReader.validatePath())
    {
        return exitWithError(pathError.value());
    }
    if (auto pathError = inputDataReader.validatePath())
    {
        return exitWithError(pathError.value());
    }

    if (auto error = configDataReader.readData())
    {
        return exitWithError(error.value());
    }
    if (auto error = inputDataReader.readData())
    {
        return exitWithError(error.value());
    }

    for (Predicate* predicate : predicatesHolder.getPredicates())
    {
        if (!predicate->compare(symbolsHolder.getUniqueCounters().at(predicate->getSymbolHolder())))
        {
            return exitSuccessfully("File doesn't fit the policy");
        }
    }
    return exitSuccessfully("File does fit the policy");
}
