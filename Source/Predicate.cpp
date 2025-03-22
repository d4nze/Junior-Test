#include "Predicate.hpp"

Predicate::Predicate(char symbol)
    : m_symbol(symbol)
    , m_count(-1)
{}

char Predicate::getSymbol() const
{
    return m_symbol;
}

std::int32_t Predicate::getCount() const
{
    return m_count;
}
