#include "PredicateMore.hpp"

PredicateMore::PredicateMore(const Symbol& symbolHolder, std::int32_t requires)
    : Predicate(symbolHolder, requires) {}

bool PredicateMore::compare(std::int32_t compareTo) const
{
    return m_requires > compareTo;
}
