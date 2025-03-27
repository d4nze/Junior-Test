#include "PredicateValidator.hpp"

#include <limits>

PredicateValidator::PredicateValidator(std::ifstream& configFile)
    : m_symbol()
    , m_predicate()
    , m_count(-1)
    , m_errorMessage(generateErrorMessage(configFile))
{}

const Symbol& PredicateValidator::getSymbol() const
{
    return m_symbol;
}

const std::string& PredicateValidator::getPredicateString() const
{
    return m_predicate;
}

std::int32_t PredicateValidator::getCount() const
{
    return m_count;
}

message_t PredicateValidator::getErrorMessage() const
{
    return m_errorMessage;
}

message_t PredicateValidator::generateErrorMessage(std::ifstream& configFile)
{
    if (message_t error = checkSymbol(configFile))
    {
        return error;
    }
    if (message_t error = checkPredicate(configFile))
    {
        return error;
    }
    if (message_t error = checkCount(configFile))
    {
        return error;
    }
    return std::nullopt;
}

message_t PredicateValidator::checkSymbol(std::ifstream& configFile)
{
    if (configFile.eof())
    {
        return "Symbol part is empty.";
    }

    std::string symbolPart;
    configFile >> symbolPart;

    if (symbolPart.size() < 3)
    {
        return "Symbol incorrect syntax.";
    }
    if (symbolPart[0] != '\'')
    {
        return "Missing opening '.";
    }
    if (symbolPart.back() != '\'')
    {
        return "Missing closing '.";
    }

    std::size_t lenght = Symbol::predictSymbolLenght(symbolPart[1]);
    if (lenght == 0 || lenght + 2 != symbolPart.size())
    {
        return "Unsupported character: " + symbolPart.substr(1, symbolPart.size() - 2) + ".";
    }
    std::string sSymbol = symbolPart.substr(1, lenght);
    m_symbol = Symbol(sSymbol);

    return std::nullopt;
}

message_t PredicateValidator::checkPredicate(std::ifstream& configFile)
{
    if (configFile.eof())
    {
        return "Predicate part is empty.";
    }
    
    std::string predicatePart;
    configFile >> predicatePart;

    if (predicatePart != "==" && predicatePart != ">" && predicatePart != "<")
    {
        return "Predicate must be '=='/'<'/'>'";
    }

    m_predicate = predicatePart;
    return std::nullopt;
}

message_t PredicateValidator::checkCount(std::ifstream& configFile)
{
    if (configFile.eof())
    {
        return "Count part is empty.";
    }
    
    std::string countPart;
    configFile >> countPart;
    std::size_t index;
    std::int64_t llCount = std::stoll(countPart, &index);
    
    if (index != countPart.length())
    {
        return "Invalid characters found in input string";
    }
    if (llCount < std::numeric_limits<std::int32_t>::min() ||
        llCount > std::numeric_limits<std::int32_t>::max())
    {
        return "Value is out of range for int32_t";
    }
    
    m_count = static_cast<std::int32_t>(llCount);
    return std::nullopt;
}

bool PredicateValidator::isNumber(char symbol) const
{
    return symbol >= '0' && symbol <= '9';
}
