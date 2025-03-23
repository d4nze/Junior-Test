#include "PredicateLess.hpp"

PredicateLess::PredicateLess(const SymbolHolder& symbolHolder, std::int32_t requires)
    : Predicate(symbolHolder, requires) {}

bool PredicateLess::compare(std::int32_t compareTo) const
{
    return m_requires < compareTo;
}
