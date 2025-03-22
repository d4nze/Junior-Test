#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

class Instruction
{
public:
    Instruction(char symbol);
    virtual ~Instruction() = default;

    virtual bool check() const = 0;
    char getSymbol() const;

private:
    char m_symbol;
};

#endif