#ifndef INPUT_CHUNK_READER_HPP
#define INPUT_CHUNK_READER_HPP

#include <fstream>
#include <string_view>

#include "Message.hpp"
#include "SymbolsHolder.hpp"

class InputChunkReader
{
public:
    InputChunkReader();
    InputChunkReader(std::string_view inputFilePath,
                     const uniques_t& uniques,
                     std::size_t start,
                     std::size_t end);

    message_t readData();

    SymbolsHolder& getSymbolsHolder();
    const SymbolsHolder& getSymbolsHolder() const;

private:
    std::string_view m_inputFilePath;
    SymbolsHolder m_symbolsHolder;
    std::size_t m_start;
    std::size_t m_end;
};

#endif
