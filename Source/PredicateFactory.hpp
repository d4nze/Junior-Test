#ifndef PREDICATE_FACTORY_HPP
#define PREDICATE_FACTORY_HPP

#include "Predicate.hpp"

class PredicateFactory
{
public:
    static Predicate* createPredicate(const Symbol& symbol,
                                      std::int32_t requires,
                                      const std::string& predicate);
};

#endif
