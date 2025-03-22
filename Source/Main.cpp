#include <iostream>

#include "PathValidator.hpp"

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
    std::string path(argv[1]);
    PathValidator inputPathValidator(path);
    if (!inputPathValidator.isValid())
    {
        return exitWithError("Can't open input file. " + inputPathValidator.getErrorMessage());
    }
    std::system("pause");
    return 0;
}
