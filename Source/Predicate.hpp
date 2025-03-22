#ifndef PREDICATE_HPP
#define PREDICATE_HPP

#include <cstdint>

class Predicate
{
public:
    Predicate(char symbol);
    virtual ~Predicate() = default;

    virtual bool check() const = 0;
    char getSymbol() const;
    std::int32_t getCount() const;

private:
    char m_symbol;
    std::int32_t m_count;
};

#endif
