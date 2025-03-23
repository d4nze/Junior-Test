#include "SymbolHolder.hpp"

#include <algorithm>

SymbolHolder::SymbolHolder(const std::string& symbolData) : m_data(symbolData) {}

const char* SymbolHolder::getData() const
{
    return m_data.c_str();
}

std::size_t SymbolHolder::getSize() const
{
    return m_data.size();
}

bool SymbolHolder::operator==(const SymbolHolder& other) const
{
    return m_data == other.m_data;
}

// Это ГПТ
std::size_t SymbolHolder::predictSymbolLenght(char beggining)
{
    unsigned char uBeggining = static_cast<unsigned char>(beggining);
    if ((uBeggining & 0x80) == 0)
    {
        return 1;
    }
    if ((uBeggining & 0xE0) == 0xC0)
    {
        return 2;
    }
    if ((uBeggining & 0xF0) == 0xE0)
    {
        return 3;
    }
    if ((uBeggining & 0xF8) == 0xF0)
    {
        return 4;
    }
    return 0;
}

// И это тоже
bool SymbolHolder::isStartOfSymbol(char part)
{
    return (part & 0xC0) == 0x80;
}
