#include "PathValidator.hpp"
#include <filesystem>

PathValidator::PathValidator(std::string_view path)
    : m_errorMessage(generateErrorMessage(path))
{}

bool PathValidator::isValid() const
{
    return !m_errorMessage.has_value();
}

std::string PathValidator::getErrorMessage() const
{
    return m_errorMessage.value_or("Unexpected error: can't get optional error message");
}

std::optional<std::string> PathValidator::generateErrorMessage(std::string_view path) const
{
    if (!std::filesystem::exists(path))
    {
        return "Invalide path.";
    }
    else if (!std::filesystem::is_regular_file(path))
    {
        return "Path is not a file.";
    }
    else if (std::filesystem::path(path).extension() != ".txt")
    {
        return "Path must be an TXT file.";
    }
    return std::nullopt;
}
