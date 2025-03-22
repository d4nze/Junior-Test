#include "InstructionValidator.hpp"
#include <sstream>

InstructionValidator::InstructionValidator(std::string_view instruction)
    : m_symbol('\0')
    , m_condition('\0')
    , m_count(-1)
    , m_errorMessage(generateErrorMessage(instruction))
{}

bool InstructionValidator::isValid() const
{
    return !m_errorMessage.has_value();
}

char InstructionValidator::getSymbol() const
{
    return m_symbol;
}

char InstructionValidator::getCondition() const
{
    return m_condition;
}

std::int32_t InstructionValidator::getCount() const
{
    return m_count;
}

std::string InstructionValidator::getErrorMessage() const
{
    return m_errorMessage.value_or("Unexpected error: can't get optional error message");
}

std::optional<std::string> InstructionValidator::generateErrorMessage(std::string_view instruction)
{
    std::string part;
    std::stringstream instructionStream(instruction.data());
    instructionStream >> part;
    if (part != "ПРИСУТСТВУЕТ")
    {
        return "Missing 'ПРИСУТСТВУЕТ' keyword.";
    }
    instructionStream >> part;
    if (part != "СИМВОЛ")
    {
        return "Missing 'СИМВОЛ' keyword.";
    }
    instructionStream >> part;
    if (part.size() < 3)
    {
        return "Invalid symbol sintax.";
    }
    if (part.size() > 3)
    {
        return "Symbol must be 1 character long.";
    }
    if (part[0] != '«')
    {
        return "Missing '\"' symbol.";
    }
    m_symbol = part[1];
    if (part[0] != '»')
    {
        return "Missing '\"' symbol.";
    }
    instructionStream >> part;
    if (part.size() != 1)
    {
        return "Condition must be 1 character long.";
    }
    m_condition = part[0];
    if (m_condition != '<' && m_condition != '=' && m_condition != '>')
    {
        return "Condition must be '<', '=' or '>'.";
    }
    instructionStream >> part;
    if (part.empty())
    {
        return "Missing count.";
    }
    if (!isNumber(part[0]) && part[0] != L'-')
    {
        return "Count must be a number.";
    }
    for (std::size_t i = 1; i < part.size(); ++i)
    {
        if (!isNumber(part[i]))
        {
            return "Count must be a number.";
        }
    }
    m_count = std::stoi(part);
    instructionStream >> part;
    if (part != "РАЗ")
    {
        return "Missing 'РАЗ' keyword.";
    }
    if (!instructionStream.eof())
    {
        return "Unexpected symbols after 'РАЗ' keyword.";
    }
    return std::nullopt;
}

bool InstructionValidator::isNumber(char symbol) const
{
    return symbol >= '0' && symbol <= '9';
}
