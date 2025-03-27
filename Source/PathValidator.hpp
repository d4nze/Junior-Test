#ifndef PATH_VALIDATOR_HPP
#define PATH_VALIDATOR_HPP

#include "Message.hpp"

class PathValidator
{
public:
    static message_t generateErrorMessage(std::string_view path);
};

#endif
