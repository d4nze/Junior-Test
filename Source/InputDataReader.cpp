#include "InputDataReader.hpp"
#include "PathValidator.hpp"

#include <fstream>

InputDataReader::InputDataReader(std::string_view inputFilePath, SymbolsHolder& symbolsHolder)
    : m_inputFilePath(inputFilePath)
    , m_symbolsHolder(symbolsHolder)
    , m_chunkSize(1000000000)
    , m_chunkReaders()
{}

message_t InputDataReader::validatePath() const
{
    if (message_t pathError = PathValidator::generateErrorMessage(m_inputFilePath))
    {
        return "Can't open input file. " + pathError.value();
    }
    return no_message;
}

message_t InputDataReader::generateIndices()
{
    std::vector<std::size_t> chunkIndices;
    std::ifstream inputFile(m_inputFilePath.data());
    if (!inputFile.is_open())
    {
        return "Can't open input file.";
    }
    inputFile.seekg(0, std::ios::end);
    std::size_t fileSize = inputFile.tellg();
    for (std::size_t i = 0; i < fileSize; i += m_chunkSize)
    {
        bool startLocated = false;
        const std::size_t countMin = std::min<std::size_t>(i, 3);
        for (std::size_t j = 0; j <= countMin; j++)
        {
            inputFile.seekg(i - j, std::ios::beg);
            char character;
            inputFile.get(character);
            if (Symbol::predictSymbolLenght(character) != 0)
            {
                startLocated = true;
                chunkIndices.push_back(i - j);
                break;
            }
        }
        if (!startLocated)
        {
            return "Failed to locate start of the symbol.";
        }
        chunkIndices.push_back(i);
    }
    inputFile.close();
    chunkIndices.push_back(fileSize);
    for (std::size_t i = 0; i < chunkIndices.size() - 1; i++)
    {
        const uniques_t& uniques = m_symbolsHolder.getUniques();
        std::size_t start = chunkIndices[i];
        std::size_t end = chunkIndices[i + 1];
        m_chunkReaders.emplace_back(m_inputFilePath, uniques, start, end);
    }
    return no_message;
}

message_t InputDataReader::readData()
{
    for (InputChunkReader& chunkReader : m_chunkReaders)
    {
        m_chunkFutures.push_back(std::async(
            &InputChunkReader::readData,
            &chunkReader
        ));
    }
    while (!m_chunkReaders.empty())
    {
        if (message_t readError = m_chunkFutures.front().get())
        {
            m_chunkFutures.clear();
            return readError;
        }
        applyChanges(m_chunkReaders.front().getSymbolsHolder().getUniqueCounters());
        m_chunkReaders.pop_front();
        m_chunkFutures.pop_front();
    }
    return no_message;
}

void InputDataReader::applyChanges(const unique_counters_t& uniqueCounters)
{
    for (auto [symbol, count] : uniqueCounters)
    {
        m_symbolsHolder.getUniqueCounter(symbol) += count;
    }
}
