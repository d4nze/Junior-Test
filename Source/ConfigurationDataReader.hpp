#ifndef CONFIGURATION_DATA_READER_HPP
#define CONFIGURATION_DATA_READER_HPP

#include <fstream>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>

#include "Symbol.hpp"
#include "Predicate.hpp"

class ConfigurationDataReader
{
public:
    ConfigurationDataReader(std::string_view configFilePath,
                            std::vector<Predicate*>& predicates,
                            std::set<Symbol>& uniqueSymbols,
                            std::map<Symbol, std::int32_t>& symbolCounters);
    
    std::optional<std::string> readData();

private:
    std::string_view m_configFilePath;
    std::vector<Predicate*>& m_predicates;
    std::set<Symbol>& m_uniqueSymbols;
    std::map<Symbol, std::int32_t>& m_symbolCounters;
    std::string m_part;
};

#endif
