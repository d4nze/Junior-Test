#ifndef SYMBOLS_HOLDER_HPP
#define SYMBOLS_HOLDER_HPP

#include <map>
#include <set>
#include <optional>

#include "Symbol.hpp"

using uniques_t = std::set<Symbol>;
using unique_counters_t = std::map<Symbol, std::int32_t>;

class SymbolsHolder
{
public:
    SymbolsHolder(const uniques_t& uniques);
    SymbolsHolder() = default;

    bool hasSymbol(const Symbol& symbol) const;
    void addSymbol(const Symbol& symbol);

    std::int32_t& getUniqueCounter(const Symbol& symbol);
    const std::int32_t& getUniqueCounter(const Symbol& symbol) const;

    uniques_t& getUniques();
    const uniques_t& getUniques() const;

    unique_counters_t& getUniqueCounters();
    const unique_counters_t& getUniqueCounters() const;

private:
    uniques_t m_uniques;
    unique_counters_t m_uniqueCounters;
};

#endif
