#ifndef INSTRUCTION_VALIDATOR_HPP
#define INSTRUCTION_VALIDATOR_HPP

#include <string>
#include <optional>

class InstructionValidator
{
public:
    InstructionValidator(std::string_view instruction);

    bool isValid() const;

    char getSymbol() const;
    char getCondition() const;
    std::int32_t getCount() const;
    std::string getErrorMessage() const;

private:
    std::optional<std::string> generateErrorMessage(std::string_view instruction);
    bool isNumber(char symbol) const;

private:
    char m_symbol;
    char m_condition;
    std::int32_t m_count;
    std::optional<std::string> m_errorMessage;
};

#endif
