#ifndef CONFIGURATION_DATA_READER_HPP
#define CONFIGURATION_DATA_READER_HPP

#include "Message.hpp"
#include "PredicatesHolder.hpp"
#include "SymbolsHolder.hpp"

class ConfigurationDataReader
{
public:
    ConfigurationDataReader(std::string_view configFilePath,
                            PredicatesHolder& predicatesHolder,
                            SymbolsHolder& symbolsHolder);
    
    message_t validatePath() const;
    message_t readData();

private:
    std::string_view m_configFilePath;
    PredicatesHolder& m_predicatesHolder;
    SymbolsHolder& m_symbolsHolder;
    std::string m_part;
};

#endif
