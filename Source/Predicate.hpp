#ifndef PREDICATE_HPP
#define PREDICATE_HPP

#include <initializer_list>
#include <array>

class Predicate
{
public:
    Predicate(std::initializer_list<char>&& symbol, std::int32_t requires);
    virtual ~Predicate() = default;

    virtual bool compare(std::int32_t compareTo) const = 0;

    std::size_t getSymbolLenght() const;
    char* getSymbol() const;
    std::int32_t getCount() const;

private:
    std::size_t m_symbolLenght;
    char* m_symbol;
    std::int32_t m_requires;
};

#endif
