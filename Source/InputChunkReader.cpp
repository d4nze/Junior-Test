#include "InputChunkReader.hpp"

InputChunkReader::InputChunkReader()
    : m_inputFilePath()
    , m_symbolsHolder()
    , m_start(0)
    , m_end(0)
{}

InputChunkReader::InputChunkReader(std::string_view inputFilePath,
                                   const uniques_t& uniques,
                                   std::size_t start,
                                   std::size_t end)
    : m_inputFilePath(inputFilePath)
    , m_symbolsHolder(uniques)
    , m_start(start)
    , m_end(end)
{}

#include <iostream>
#include <mutex>
static std::mutex mtx;

message_t InputChunkReader::readData()
{
    char symbolPart;
    std::ifstream inputFile(m_inputFilePath.data());
    inputFile.seekg(m_start, std::ios::beg);
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << m_start << " : " << m_end << "\n";
    }
    while (m_start++ <= m_end && inputFile >> symbolPart)
    {
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
        Symbol symbol(sSymbol);
        if (m_symbolsHolder.hasSymbol(symbol))
        {
            m_symbolsHolder.getUniqueCounter(symbol)++;
        }
    }
    return no_message;
}

SymbolsHolder& InputChunkReader::getSymbolsHolder()
{
    return m_symbolsHolder;
}

const SymbolsHolder& InputChunkReader::getSymbolsHolder() const
{
    return m_symbolsHolder;
}
