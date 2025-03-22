#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <cstdint>

class Instruction
{
public:
    Instruction(char symbol);
    virtual ~Instruction() = default;

    virtual bool check() const = 0;
    char getSymbol() const;
    std::int32_t getCount() const;

private:
    char m_symbol;
    std::int32_t m_count;
};

#endif
