#ifndef CONFIGURATION_DATA_READER_HPP
#define CONFIGURATION_DATA_READER_HPP

#include <fstream>
#include <optional>
#include <string>

#include "PredicatesHolder.hpp"
#include "SymbolsHolder.hpp"

class ConfigurationDataReader
{
public:
    ConfigurationDataReader(std::string_view configFilePath,
                            PredicatesHolder& predicatesHolder,
                            SymbolsHolder& symbolsHolder);
    
    std::optional<std::string> readData();

private:
    std::string_view m_configFilePath;
    PredicatesHolder& m_predicatesHolder;
    SymbolsHolder& m_symbolsHolder;
    std::string m_part;
};

#endif
