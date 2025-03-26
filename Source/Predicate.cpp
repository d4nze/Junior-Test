#include "Predicate.hpp"
#include <algorithm>

Predicate::Predicate(const Symbol& symbolHolder, std::int32_t requires)
    : m_symbolHolder(symbolHolder)
    , m_requires(requires)
{}

const Symbol& Predicate::getSymbolHolder() const
{
    return m_symbolHolder;
}

std::int32_t Predicate::getRequired() const
{
    return m_requires;
}
