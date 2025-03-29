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

    PredicatesHolder predicatesHolder;
    SymbolsHolder symbolsHolder;
    ConfigurationDataReader configDataReader("Configuration.txt", predicatesHolder, symbolsHolder);

    if (message_t pathError = configDataReader.validatePath())
    {
        return exitWithError(pathError.value());
    }
    if (message_t readError = configDataReader.readData())
    {
        return exitWithError(readError.value());
    }

    InputDataReader inputDataReader(argv[1], symbolsHolder);
    if (message_t pathError = inputDataReader.validatePath())
    {
        return exitWithError(pathError.value());
    }
    if (message_t fileError = inputDataReader.generateIndices())
    {
        return exitWithError(fileError.value());
    }
    if (message_t readError = inputDataReader.readData())
    {
        return exitWithError(readError.value());
    }

    if (!predicatesHolder.fitsPolicy(symbolsHolder.getUniqueCounters()))
    {
        return exitSuccessfully("File doesn't fit the policy");
    }
    return exitSuccessfully("File does fit the policy");
}
