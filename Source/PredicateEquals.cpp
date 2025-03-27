#include "PredicateEquals.hpp"

PredicateEquals::PredicateEquals(const Symbol& symbol, std::int32_t requires)
    : Predicate(symbol, requires) {}

bool PredicateEquals::compare(std::int32_t compareTo) const
{
    return m_requires == compareTo;
}
