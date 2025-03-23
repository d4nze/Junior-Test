#include "SymbolHolder.hpp"

#include <algorithm>

SymbolHolder::SymbolHolder() : m_size(0)
{
    for (std::size_t i = 0; i < 5; i++)
    {
        m_data[i] = '\0';
    }
}

SymbolHolder::SymbolHolder(const std::string& symbolData)
    : m_size(std::min<std::size_t>(4, symbolData.size()))
{
    for (std::size_t i = 0; i < m_size; i++)
    {
        m_data[i] = symbolData[i];
    }
    m_data[m_size] = '\0';
}

SymbolHolder::SymbolHolder(const SymbolHolder& other) : m_size(other.m_size)
{
    for (std::size_t i = 0; i < 5; i++)
    {
        m_data[i] = other.m_data[i];
    }
}

const char* SymbolHolder::getData() const
{
    return m_data;
}

std::size_t SymbolHolder::getSize() const
{
    return m_size;
}

bool SymbolHolder::operator<(const SymbolHolder& other) const
{
    if (m_size != other.m_size)
    {
        return m_size < other.m_size;
    }
    for (std::size_t i = 0; i < m_size; i++)
    {
        if (m_data[i] != other.m_data[i])
        {
            return static_cast<std::int32_t>(m_data[i]) < static_cast<std::int32_t>(other.m_data[i]);
        }
    }
    return false;
}

bool SymbolHolder::operator==(const SymbolHolder& other) const
{
    for (std::size_t i = 0; i < 4; i++)
    {
        if (m_data[i] != other.m_data[i])
        {
            return false;
        }
    }
    return true;
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
