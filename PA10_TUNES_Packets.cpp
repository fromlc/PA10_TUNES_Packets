//------------------------------------------------------------------------------
// PA10_TUNES_Packets.cpp
//------------------------------------------------------------------------------
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

//------------------------------------------------------------------------------
// input file name and format
//------------------------------------------------------------------------------
const std::string INPUT_FILENAME = "TUNES_song.txt";

// IP Address (10 bytes ASCII)
const int BYTELEN_IP_ADDRESS = 10;
// Protocol ID (3 bytes ASCII)
const int BYTELEN_PROTOCOL_ID = 3;
// Sequence number (10 bytes ASCII)
const int BYTELEN_SEQNO = 10;
// Data byte length (4 bytes ASCII)
const int BYTELEN_DATALEN = 4;

// combined length of line header fields
constexpr int BYTELEN_LINE_HEADER =
BYTELEN_IP_ADDRESS + BYTELEN_PROTOCOL_ID + BYTELEN_SEQNO + BYTELEN_DATALEN;

// 192.168.1.10
uint32_t MY_IP_ADDRESS = 0xc0a8010a;

// TUNES protocol ID
constexpr int PROTOCOL_ID_TUNES = 10;

//------------------------------------------------------------------------------
// We put the header field pointers in a struct so the destructor 
// Will delete memory for us at the right time.
//------------------------------------------------------------------------------
struct FileData
{
    char* pIPAddress;
    char* pProtocolID;
    char* pSeqno;
    char* pDataLen;

    uint32_t ipAddress;
    uint32_t seqno;
    uint8_t protocolID;

    // constructor
    FileData() : ipAddress(0), seqno(0), protocolID(0)
    {
        // Dynamically allocate buffer space for each header field.
        // Use the constants above for appropriate lengths.
        // Add 1 to each length to make room for a zero terminator byte!
        //#TODO modify these initializations.
        pIPAddress = nullptr;
        pProtocolID = nullptr;
        pSeqno = nullptr;
        pDataLen = nullptr;
    }

    // destructor
    ~FileData()
    {
        // Delete each header field buffer
        //#TODO
    }
};

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
void protocolAnalyzer();
void buildSongMap(std::map<uint32_t, std::string>& songMap);
void displaySongLines(std::map<uint32_t, std::string>& songMap);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main()
{
    // isolate memory allocations for heap profiling 
    protocolAnalyzer();

    std::cout << "\nType any key to exit app...\n";
    std::cin.get();
}

//------------------------------------------------------------------------------
// - does all protocol analysis work
// - builds song line map
// - displays song line map
// - keeps all memory allocations separate from main for heap profiling 
//------------------------------------------------------------------------------
void protocolAnalyzer()
{
    std::map<uint32_t, std::string> songMap;

    buildSongMap(songMap);
    displaySongLines(songMap);
}

//------------------------------------------------------------------------------
// read song lines from input file and insert lines into passed map
//------------------------------------------------------------------------------
void buildSongMap(std::map<uint32_t, std::string>& songMap)
{
    // This struct contains all field header buffers
    FileData fd;

    std::ifstream input(INPUT_FILENAME);
    std::string line;
    while (getline(input, line))
    {
        // line.c_str() is the actual string for the file line
        // this is not an allocation, only a pointer to std::string data
        const char* pLine = line.c_str();

        // Display all lines in file
        // These will include lines that aren't part of the song
        // Song lines will be out of order
        std::cout << pLine << "\n";

        // Copy the IP address into the FileData address buffer fd.pIPAddress
        // Use the C++ library function memcpy().
        // Then add the correct number of bytes to pLine,
        // so that pLine points to the next header field.
        // Store a char(0) at the end of the pIPAddress buffer.
        //#TODO

        // Copy the Protocol ID header field the same way.
        //#TODO

        // Copy the Sequence Number header field the same way.
        //#TODO

        // Copy the Data Length header field the same way.
        //#TODO

        // Convert the ASCII Sequence Number to a uint32_t number.
        // The Sequence Number is in hexadecimal format,
        // so the 16 argument indicates hex number conversion.
        //#TODO uncomment next line after you have a valid fd.seqno
        //fd.seqno = std::stoi(fd.pSeqno, nullptr, 16);

        // Convert the ASCII protocol ID to a uint8_t number the same way.
        // You'll need a static_cast for this one.
        //#TODO

        // Convert the ASCII IP number to a uint32_t number.
        // IP numbers are too long for std::stoi(), so use std::strtoll().
        // You need this dummy pointer for the strtoll() reference parameter.
        char* pEnd {};
        //#TODO

        // Convert pLine to std::string and add key value pair to map
        //#TODO
    }
    std::cout << "\n";
    // done with file
    input.close();
}

//------------------------------------------------------------------------------
// display song lines in map
//------------------------------------------------------------------------------
void displaySongLines(std::map<uint32_t, std::string>& songMap)
{
    // Display song lines in order 
    //#TODO
}
