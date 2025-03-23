#ifndef PATH_VALIDATOR_HPP
#define PATH_VALIDATOR_HPP

#include <string>
#include <optional>

class PathValidator
{
public:
    static std::optional<std::string> generateErrorMessage(std::string_view path);
};

#endif
