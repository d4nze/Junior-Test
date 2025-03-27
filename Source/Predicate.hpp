#ifndef PREDICATE_HPP
#define PREDICATE_HPP

#include "Symbol.hpp"

class Predicate
{
public:
    Predicate(const Symbol& symbol, std::int32_t requires);
    virtual ~Predicate() = default;

    virtual bool compare(std::int32_t compareTo) const = 0;

    const Symbol& getSymbol() const;
    std::int32_t getRequired() const;

protected:
    const Symbol m_symbol;
    std::int32_t m_requires;
};

#endif
