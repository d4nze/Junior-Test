#include "InputDataReader.hpp"

InputDataReader::InputDataReader(std::string_view inputFilePath,
                                 const std::set<Symbol>& uniqueSymbols,
                                 std::map<Symbol, std::int32_t>& symbolCounters)
    : m_inputFilePath(inputFilePath)
    , m_uniqueSymbols(uniqueSymbols)
    , m_symbolCounters(symbolCounters)
{}

std::optional<std::string> InputDataReader::readData()
{
    std::ifstream inputFile(m_inputFilePath.data());
    if (!inputFile.is_open())
    {
        return "Can't open input file.";
    }

    for (char symbolPart; inputFile >> symbolPart;)
    {
        if (symbolPart == '\n')
        {
            continue;
        }
        std::size_t lenght = Symbol::predictSymbolLenght(symbolPart);
        if (lenght == 0)
        {
            return "Unsupported character.";
        }
        std::string sSymbol(lenght, symbolPart);
        for (std::size_t i = 1; i < lenght; i++)
        {
            inputFile >> symbolPart;
            sSymbol[i] = symbolPart;
        }
        Symbol symbolHolder(sSymbol);
        if (m_uniqueSymbols.find(symbolHolder) != m_uniqueSymbols.end())
        {
            m_symbolCounters[symbolHolder]++;
        }
    }
    return std::nullopt;
}
