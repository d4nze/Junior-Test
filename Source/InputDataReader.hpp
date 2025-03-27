#ifndef INPUT_DATA_READER_HPP
#define INPUT_DATA_READER_HPP

#include <fstream>
#include <optional>
#include <string>

#include "Message.hpp"
#include "SymbolsHolder.hpp"

class InputDataReader
{
public:
    InputDataReader(std::string_view inputFilePath, SymbolsHolder& symbolsHolder);
    
    message_t validatePath() const;
    message_t readData();

private:
    std::string_view m_inputFilePath;
    SymbolsHolder& m_symbolsHolder;
};

#endif
