#include "PredicateValidator.hpp"

#include <limits>

PredicateValidator::PredicateValidator(std::ifstream& configFile)
    : m_symbol()
    , m_predicate()
    , m_count(-1)
    , m_errorMessage(generateErrorMessage(configFile))
{}

bool PredicateValidator::isValid() const
{
    return !m_errorMessage.has_value();
}

const SymbolHolder& PredicateValidator::getSymbol() const
{
    return m_symbol;
}

const std::string& PredicateValidator::getPredicate() const
{
    return m_predicate;
}

std::int32_t PredicateValidator::getCount() const
{
    return m_count;
}

std::string PredicateValidator::getErrorMessage() const
{
    return m_errorMessage.value_or("Unexpected error: can't get optional error message");
}

std::optional<std::string> PredicateValidator::generateErrorMessage(std::ifstream& configFile)
{
    if (auto error = checkSymbol(configFile))
    {
        return error;
    }
    if (auto error = checkPredicate(configFile))
    {
        return error;
    }
    if (auto error = checkCount(configFile))
    {
        return error;
    }
    return std::nullopt;
}

std::optional<std::string> PredicateValidator::checkSymbol(std::ifstream& configFile)
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

    std::size_t lenght = SymbolHolder::predictSymbolLenght(symbolPart[1]);
    std::string sSymbol = symbolPart.substr(1, lenght);
    if (lenght == 0 || lenght + 2 != symbolPart.size())
    {
        return "Unsupported character: " + sSymbol + ".";
    }
    m_symbol = SymbolHolder(sSymbol);

    return std::nullopt;
}

std::optional<std::string> PredicateValidator::checkPredicate(std::ifstream& configFile)
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

std::optional<std::string> PredicateValidator::checkCount(std::ifstream& configFile)
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
