#ifndef SYMBOL_HOLDER_HPP
#define SYMBOL_HOLDER_HPP

#include <string>

class SymbolHolder
{
public:
    SymbolHolder();
    SymbolHolder(const std::string& symbolData);
    SymbolHolder(const SymbolHolder& other);

    const char* getData() const;
    std::size_t getSize() const;

    bool operator==(const SymbolHolder& other) const;
    
    static std::size_t predictSymbolLenght(char beggining);
    static bool isStartOfSymbol(char part);

private:
    char m_data[5];
    std::size_t m_size;
};

#endif
