#include "SymbolsHolder.hpp"

uniques_t& SymbolsHolder::getUniques()
{
    return m_uniques;
}

const uniques_t& SymbolsHolder::getUniques() const
{
    return m_uniques;
}

unique_counters_t& SymbolsHolder::getUniqueCounters()
{
    return m_uniqueCounters;
}

const unique_counters_t& SymbolsHolder::getUniqueCounters() const
{
    return m_uniqueCounters;
}
