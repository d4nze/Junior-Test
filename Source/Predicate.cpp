#include "Predicate.hpp"
#include <algorithm>

Predicate::Predicate(const SymbolHolder& symbolHolder, std::int32_t requires)
    : m_symbolHolder(symbolHolder)
    , m_requires(requires)
{}

const SymbolHolder& Predicate::getSymbolHolder() const
{
    return m_symbolHolder;
}

std::int32_t Predicate::getRequired() const
{
    return m_requires;
}
