#include "PredicatesHolder.hpp"

PredicatesHolder::~PredicatesHolder()
{
    for (Predicate* predicate : m_predicates)
    {
        delete predicate;
    }
}

void PredicatesHolder::addPredicate(Predicate* predicate)
{
    m_predicates.push_back(predicate);
}

bool PredicatesHolder::fitsPolicy(const unique_counters_t& uniqueCounters) const
{
    for (Predicate* predicate : m_predicates)
    {
        if (!predicate->compare(uniqueCounters.at(predicate->getSymbol())))
        {
            return false;
        }
    }
    return true;
}

predicates_t& PredicatesHolder::getPredicates()
{
    return m_predicates;
}

const predicates_t& PredicatesHolder::getPredicates() const
{
    return m_predicates;
}
