#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <optional>
#include <string>

using message_t = std::optional<std::string>;
constexpr std::nullopt_t no_message = std::nullopt;

#endif
