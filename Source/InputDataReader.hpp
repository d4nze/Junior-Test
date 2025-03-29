#ifndef INPUT_DATA_READER_HPP
#define INPUT_DATA_READER_HPP

#include <future>
#include <list>

#include "InputChunkReader.hpp"
#include "Message.hpp"
#include "SymbolsHolder.hpp"

class InputDataReader
{
public:
    InputDataReader(std::string_view inputFilePath, SymbolsHolder& symbolsHolder);
    
    message_t validatePath() const;
    message_t generateIndices();
    message_t readData();

private:
    void applyChanges(const unique_counters_t& uniqueCounters);

private:
    std::string_view m_inputFilePath;
    SymbolsHolder& m_symbolsHolder;
    std::mutex m_chunkMutex;
    std::list<InputChunkReader> m_chunkReaders;
    std::list<std::future<message_t>> m_chunkFutures;
    const std::size_t m_chunkSize;
};

#endif
