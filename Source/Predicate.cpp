#include "Predicate.hpp"
#include <algorithm>

Predicate::Predicate(std::initializer_list<char>&& symbol, std::int32_t requires)
    : m_symbolLenght(symbol.size())
    , m_symbol(new char[m_symbolLenght])
    , m_requires(requires)
{
    std::copy(symbol.begin(), symbol.end(), m_symbol);
}

std::size_t Predicate::getSymbolLenght() const
{
    return m_symbolLenght;
}

char* Predicate::getSymbol() const
{
    return m_symbol;
}

std::int32_t Predicate::getCount() const
{
    return m_requires;
}
