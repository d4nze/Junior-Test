#ifndef CONFIGURATION_DATA_READER_HPP
#define CONFIGURATION_DATA_READER_HPP

#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "Predicate.hpp"
#include "SymbolsHolder.hpp"

class ConfigurationDataReader
{
public:
    ConfigurationDataReader(std::string_view configFilePath,
                            std::vector<Predicate*>& predicates,
                            SymbolsHolder& symbolsHolder);
    
    std::optional<std::string> readData();

private:
    std::string_view m_configFilePath;
    std::vector<Predicate*>& m_predicates;
    SymbolsHolder& m_symbolsHolder;
    std::string m_part;
};

#endif
