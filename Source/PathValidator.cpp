#include "PathValidator.hpp"
#include <filesystem>

std::optional<std::string> PathValidator::generateErrorMessage(std::string_view path)
{
    if (!std::filesystem::exists(path))
    {
        return "Invalide path.";
    }
    if (!std::filesystem::is_regular_file(path))
    {
        return "Path is not a file.";
    }
    if (std::filesystem::path(path).extension() != ".txt")
    {
        return "Path must be an TXT file.";
    }
    return std::nullopt;
}
