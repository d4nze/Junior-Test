#ifndef PREDICATE_MORE_HPP
#define PREDICATE_MORE_HPP

#include "Predicate.hpp"

class PredicateMore : public Predicate
{
public:
    PredicateMore(const Symbol& symbolHolder, std::int32_t requires);

    bool compare(std::int32_t compareTo) const override;
};

#endif
