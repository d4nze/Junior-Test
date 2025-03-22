#include "Instruction.hpp"

Instruction::Instruction(char symbol) : m_symbol(symbol) {}

char Instruction::getSymbol() const
{
    return m_symbol;
}
