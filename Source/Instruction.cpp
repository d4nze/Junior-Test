#include "Instruction.hpp"

Instruction::Instruction(char symbol)
    : m_symbol(symbol)
    , m_count(-1)
{}

char Instruction::getSymbol() const
{
    return m_symbol;
}

std::int32_t Instruction::getCount() const
{
    return m_count;
}
