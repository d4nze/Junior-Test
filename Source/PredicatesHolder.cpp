#include "PredicatesHolder.hpp"

predicates_t& PredicatesHolder::getPredicates()
{
    return m_predicate;
}

const predicates_t& PredicatesHolder::getPredicates() const
{
    return m_predicate;
}
