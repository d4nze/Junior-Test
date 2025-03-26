#ifndef PREDICATE_VALIDATOR_HPP
#define PREDICATE_VALIDATOR_HPP

#include <fstream>
#include <string>
#include <optional>

#include "Symbol.hpp"

class PredicateValidator
{
public:
    PredicateValidator(std::ifstream& configFile);

    bool isValid() const;

    const Symbol& getSymbol() const;
    const std::string& getPredicate() const;
    std::int32_t getCount() const;
    std::string getErrorMessage() const;

private:
    std::optional<std::string> generateErrorMessage(std::ifstream& configFile);
    std::optional<std::string> checkSymbol(std::ifstream& configFile);
    std::optional<std::string> checkPredicate(std::ifstream& configFile);
    std::optional<std::string> checkCount(std::ifstream& configFile);

    bool isNumber(char symbol) const;

private:
    Symbol m_symbol;
    std::string m_predicate;
    std::int32_t m_count;
    std::optional<std::string> m_errorMessage;
};

#endif
