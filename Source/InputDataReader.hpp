#ifndef INPUT_DATA_READER_HPP
#define INPUT_DATA_READER_HPP

#include <fstream>
#include <optional>
#include <string>

#include "SymbolsHolder.hpp"

class InputDataReader
{
public:
    InputDataReader(std::string_view inputFilePath, SymbolsHolder& symbolsHolder);
    
    std::optional<std::string> readData();

private:
    std::string_view m_inputFilePath;
    SymbolsHolder& m_symbolsHolder;
};

#endif
