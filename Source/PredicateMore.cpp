#include "PredicateMore.hpp"

PredicateMore::PredicateMore(const Symbol& symbol, std::int32_t requires)
    : Predicate(symbol, requires) {}

bool PredicateMore::compare(std::int32_t compareTo) const
{
    return m_requires > compareTo;
}
