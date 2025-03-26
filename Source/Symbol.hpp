#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>

class Symbol
{
public:
    Symbol();
    Symbol(const std::string& symbolData);
    Symbol(const Symbol& other);

    const char* getData() const;
    std::size_t getSize() const;

    bool operator<(const Symbol& other) const;
    bool operator==(const Symbol& other) const;
    
    static std::size_t predictSymbolLenght(char beggining);
    static bool isStartOfSymbol(char part);

private:
    char m_data[5];
    std::size_t m_size;
};

#endif
