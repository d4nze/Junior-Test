#include "PredicateEquals.hpp"

PredicateEquals::PredicateEquals(const SymbolHolder& symbolHolder, std::int32_t requires)
    : Predicate(symbolHolder, requires) {}

bool PredicateEquals::compare(std::int32_t compareTo) const
{
    return m_requires > compareTo;
}
