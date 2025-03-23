#ifndef SYMBOL_HOLDER_HPP
#define SYMBOL_HOLDER_HPP

#include <string>

class SymbolHolder
{
public:
    SymbolHolder(const std::string& symbolData);

    const char* getData() const;
    std::size_t getSize() const;

    bool operator==(const SymbolHolder& other) const;
    
    static std::size_t predictSymbolLenght(char beggining);
    static bool isStartOfSymbol(char part);

private:
    std::string m_data;
};

#endif
