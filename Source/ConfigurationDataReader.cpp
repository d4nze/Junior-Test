#include "ConfigurationDataReader.hpp"
#include "PathValidator.hpp"
#include "PredicateFactory.hpp"
#include "PredicateValidator.hpp"

ConfigurationDataReader::ConfigurationDataReader(std::string_view configFilePath,
                                                 PredicatesHolder& predicatesHolder,
                                                 SymbolsHolder& symbolsHolder)
    : m_configFilePath(configFilePath)
    , m_predicatesHolder(predicatesHolder)
    , m_symbolsHolder(symbolsHolder)
    , m_part()
{}

std::optional<std::string> ConfigurationDataReader::validatePath() const
{
    if (auto pathError = PathValidator::generateErrorMessage(m_configFilePath))
    {
        return "Can't open configuration file. " + pathError.value();
    }
    return std::nullopt;
}

std::optional<std::string> ConfigurationDataReader::readData()
{
    std::ifstream configFile(m_configFilePath.data());
    if (!configFile.is_open())
    {
        return "Can't open predicates file.";
    }
    if (configFile.eof())
    {
        return "Configuration file is empty.";
    }

    do
    {
        PredicateValidator predicateValidator(configFile);
        if (!predicateValidator.isValid())
        {
            return predicateValidator.getErrorMessage();
        }

        const Symbol& symbol = predicateValidator.getSymbol();
        const std::string& sPredicate = predicateValidator.getPredicateString();
        std::int32_t count = predicateValidator.getCount();

        m_symbolsHolder.addSymbol(symbol);

        if (Predicate* predicate = PredicateFactory::createPredicate(symbol, count, sPredicate))
        {
            m_predicatesHolder.addPredicate(predicate);
        }
    }
    while (!configFile.eof() && configFile >> m_part && m_part == "&&");

    if (!configFile.eof())
    {
        return "Expected '&&' or end of file.";
    }

    return std::nullopt;
}
