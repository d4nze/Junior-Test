#include "Predicate.hpp"
#include <algorithm>

Predicate::Predicate(const Symbol& symbol, std::int32_t requires)
    : m_symbol(symbol)
    , m_requires(requires)
{}

const Symbol& Predicate::getSymbol() const
{
    return m_symbol;
}

std::int32_t Predicate::getRequired() const
{
    return m_requires;
}
