#ifndef PREDICATE_LESS_HPP
#define PREDICATE_LESS_HPP

#include "Predicate.hpp"

class PredicateLess : public Predicate
{
public:
    PredicateLess(const SymbolHolder& symbolHolder, std::int32_t requires);

    bool compare(std::int32_t compareTo) const override;
};

#endif
