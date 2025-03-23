#ifndef INPUT_DATA_READER_HPP
#define INPUT_DATA_READER_HPP

#include <fstream>
#include <map>
#include <optional>
#include <set>
#include <string>

#include "SymbolHolder.hpp"

class InputDataReader
{
public:
    InputDataReader(std::string_view inputFilePath,
                    const std::set<SymbolHolder>& uniqueSymbols,
                    std::map<SymbolHolder, std::int32_t>& symbolCounters);
    
    std::optional<std::string> readData();

private:
    std::string_view m_inputFilePath;
    const std::set<SymbolHolder>& m_uniqueSymbols;
    std::map<SymbolHolder, std::int32_t>& m_symbolCounters;
};

#endif
