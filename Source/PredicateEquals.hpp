#ifndef PREDICATE_EQUALS_HPP
#define PREDICATE_EQUALS_HPP

#include "Predicate.hpp"

class PredicateEquals : public Predicate
{
public:
    PredicateEquals(const Symbol& symbol, std::int32_t requires);

    bool compare(std::int32_t compareTo) const override;
};

#endif
