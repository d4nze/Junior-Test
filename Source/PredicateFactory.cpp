#include "PredicateFactory.hpp"
#include "PredicateMore.hpp"

Predicate* PredicateFactory::createPredicate(const SymbolHolder& symbolHolder,
                                             std::int32_t requires,
                                             const std::string& predicate)
{
    if (predicate == ">")
    {
        return new PredicateMore(symbolHolder, requires);
    }
    return nullptr;
}
