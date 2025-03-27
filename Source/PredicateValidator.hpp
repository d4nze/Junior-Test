#ifndef PREDICATE_VALIDATOR_HPP
#define PREDICATE_VALIDATOR_HPP

#include <fstream>

#include "Message.hpp"
#include "Symbol.hpp"

class PredicateValidator
{
public:
    PredicateValidator(std::ifstream& configFile);

    const Symbol& getSymbol() const;
    const std::string& getPredicateString() const;
    std::int32_t getCount() const;
    message_t getErrorMessage() const;

private:
    message_t generateErrorMessage(std::ifstream& configFile);
    message_t checkSymbol(std::ifstream& configFile);
    message_t checkPredicate(std::ifstream& configFile);
    message_t checkCount(std::ifstream& configFile);

    bool isNumber(char symbol) const;

private:
    Symbol m_symbol;
    std::string m_predicate;
    std::int32_t m_count;
    message_t m_errorMessage;
};

#endif
