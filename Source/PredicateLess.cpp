#include "PredicateLess.hpp"

PredicateLess::PredicateLess(const Symbol& symbol, std::int32_t requires)
    : Predicate(symbol, requires) {}

bool PredicateLess::compare(std::int32_t compareTo) const
{
    return m_requires < compareTo;
}
