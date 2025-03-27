#ifndef PREDICATES_HOLDER_HPP
#define PREDICATES_HOLDER_HPP

#include <vector>

#include "Predicate.hpp"

using predicates_t = std::vector<Predicate*>;

class PredicatesHolder
{
public:
    PredicatesHolder() = default;
    
    predicates_t& getPredicates();
    const predicates_t& getPredicates() const;

private:
    predicates_t m_predicate;
};

#endif
