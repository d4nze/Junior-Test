#ifndef PREDICATE_HPP
#define PREDICATE_HPP

#include "SymbolHolder.hpp"

class Predicate
{
public:
    Predicate(const SymbolHolder& symbolHolder, std::int32_t requires);
    virtual ~Predicate() = default;

    virtual bool compare(std::int32_t compareTo) const = 0;

    const SymbolHolder& getSymbolHolder() const;
    std::int32_t getRequired() const;

private:
    const SymbolHolder m_symbolHolder;
    std::int32_t m_requires;
};

#endif
