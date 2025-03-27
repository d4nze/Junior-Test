#ifndef PREDICATES_HOLDER_HPP
#define PREDICATES_HOLDER_HPP

#include <vector>

#include "Predicate.hpp"
#include "SymbolsHolder.hpp"

using predicates_t = std::vector<Predicate*>;

class PredicatesHolder
{
public:
    PredicatesHolder() = default;
    ~PredicatesHolder();

    void addPredicate(Predicate* predicate);
    bool fitsPolicy(const unique_counters_t& uniqueCounters) const;

    predicates_t& getPredicates();
    const predicates_t& getPredicates() const;

private:
    predicates_t m_predicates;
};

#endif
