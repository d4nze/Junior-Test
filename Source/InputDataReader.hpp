#ifndef INPUT_DATA_READER_HPP
#define INPUT_DATA_READER_HPP

#include <fstream>
#include <map>
#include <optional>
#include <set>
#include <string>

#include "Symbol.hpp"

class InputDataReader
{
public:
    InputDataReader(std::string_view inputFilePath,
                    const std::set<Symbol>& uniqueSymbols,
                    std::map<Symbol, std::int32_t>& symbolCounters);
    
    std::optional<std::string> readData();

private:
    std::string_view m_inputFilePath;
    const std::set<Symbol>& m_uniqueSymbols;
    std::map<Symbol, std::int32_t>& m_symbolCounters;
};

#endif
