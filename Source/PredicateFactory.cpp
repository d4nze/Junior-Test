#include "PredicateFactory.hpp"
#include "PredicateEquals.hpp"
#include "PredicateLess.hpp"
#include "PredicateMore.hpp"

Predicate* PredicateFactory::createPredicate(const Symbol& symbol,
                                             std::int32_t requires,
                                             const std::string& predicate)
{
    if (predicate == "==")
    {
        return new PredicateEquals(symbol, requires);
    }
    if (predicate == ">")
    {
        return new PredicateLess(symbol, requires);
    }
    if (predicate == "<")
    {
        return new PredicateMore(symbol, requires);
    }
    return nullptr;
}
