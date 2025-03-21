#ifndef PATH_VALIDATOR_HPP
#define PATH_VALIDATOR_HPP

#include <string>
#include <optional>

class PathValidator
{
public:
    PathValidator(std::string_view path);

public:
    bool isValid() const;
    std::string getErrorMessage() const;

private:
    std::optional<std::string> generateErrorMessage(std::string_view path) const;

private:
    std::optional<std::string> m_errorMessage;
};

#endif
