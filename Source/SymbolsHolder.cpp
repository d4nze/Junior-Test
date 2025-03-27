#include "SymbolsHolder.hpp"

bool SymbolsHolder::hasSymbol(const Symbol& symbol) const
{
    return m_uniques.find(symbol) != m_uniques.end();
}

void SymbolsHolder::addSymbol(const Symbol& symbol)
{
    m_uniques.insert(symbol);
    m_uniqueCounters[symbol] = 0;
}

std::int32_t& SymbolsHolder::getUniqueCounter(const Symbol& symbol)
{
    return m_uniqueCounters[symbol];
}

const std::int32_t& SymbolsHolder::getUniqueCounter(const Symbol& symbol) const
{
    return m_uniqueCounters.at(symbol);
}

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
