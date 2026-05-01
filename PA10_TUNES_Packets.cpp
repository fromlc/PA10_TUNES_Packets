//------------------------------------------------------------------------------
// PA10_grading.cpp
//------------------------------------------------------------------------------
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

//------------------------------------------------------------------------------
// input file name and format
//------------------------------------------------------------------------------
const std::string INPUT_FILENAME = "TUNES_song.txt";

// IP Address (4 byte number, 10 bytes ASCII)
const int BYTELEN_IP_ADDRESS = 10;
// Protocol ID (1 byte number, 3 bytes ASCII)
const int BYTELEN_PROTOCOL_ID = 3;
// Sequence number (4 byte number, 10 bytes ASCII)
const int BYTELEN_SEQNO = 10;
// Data byte length (2 byte number, 4 bytes ASCII)
const int BYTELEN_DATALEN = 4;

// combined length of line header fields
constexpr int BYTELEN_LINE_HEADER =
BYTELEN_IP_ADDRESS + BYTELEN_PROTOCOL_ID + BYTELEN_SEQNO + BYTELEN_DATALEN;

// 192.168.1.10
uint32_t MY_IP_ADDRESS = 0xc0a8010a;

// TUNES protocol ID
constexpr int PROTOCOL_ID_TUNES = 10;

// put pointers in struct so destructor will delete
struct FileData
{
    // constructor
    char* pIPAddress;
    char* pProtocolID;
    char* pSeqno;
    char* pDataLen;

    uint32_t ipAddress;
    uint32_t seqno;
    uint8_t protocolID;

    FileData() : ipAddress(0), seqno(0), protocolID(0)
    {
        pIPAddress = new char[BYTELEN_IP_ADDRESS + 1];
        pProtocolID = new char[BYTELEN_PROTOCOL_ID + 1];
        pSeqno = new char[BYTELEN_SEQNO + 1];
        pDataLen = new char[BYTELEN_DATALEN + 1];
    }

    // destructor
    ~FileData()
    {
        delete[] pIPAddress;
        delete[] pProtocolID;
        delete[] pSeqno;
        delete[] pDataLen;
    }
};

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
void buildSongMap(std::map<uint32_t, std::string>& songMap);
void displaySongLines(std::map<uint32_t, std::string>& songMap);
void protocolAnalyzer();

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main()
{
    protocolAnalyzer();

    //std::cout << "\nWaiting for keyboard input before terminating...\n";
    //std::cin.get();
}

//------------------------------------------------------------------------------
// isolate memory allocations 
//------------------------------------------------------------------------------
void protocolAnalyzer()
{
    std::map<uint32_t, std::string> songMap;

    buildSongMap(songMap);
    displaySongLines(songMap);

    // for memory delete tracking
    songMap.clear();
}

//------------------------------------------------------------------------------
// read song lines from input file and insert lines into passed map
//------------------------------------------------------------------------------
void buildSongMap(std::map<uint32_t, std::string>& songMap)
{
    FileData fd;

    std::ifstream input(INPUT_FILENAME);
    std::string line;
    while (getline(input, line))
    {
        // line.c_str() is the actual string for the file line
        // this is not an allocation, only a pointer to std::string data
        const char* pLine = line.c_str();

        // copy IP address
        memcpy(fd.pIPAddress, pLine, BYTELEN_IP_ADDRESS);
        pLine += BYTELEN_IP_ADDRESS;
        fd.pIPAddress[BYTELEN_IP_ADDRESS] = (char)0;

        // copy Protocol ID
        memcpy(fd.pProtocolID, pLine, BYTELEN_PROTOCOL_ID);
        pLine += BYTELEN_PROTOCOL_ID;
        fd.pProtocolID[BYTELEN_PROTOCOL_ID] = (char)0;

        // copy Sequence Number
        memcpy(fd.pSeqno, pLine, BYTELEN_SEQNO);
        pLine += BYTELEN_SEQNO;
        fd.pSeqno[BYTELEN_SEQNO] = (char)0;

        // copy Data Length in bytes
        memcpy(fd.pDataLen, pLine, BYTELEN_DATALEN);
        pLine += BYTELEN_DATALEN;
        fd.pDataLen[BYTELEN_DATALEN] = (char)0;

        // convert ASCII sequence to number 
        fd.seqno = std::stoi(fd.pSeqno, nullptr, 16);

        // convert ASCII protocol ID to number 
        fd.protocolID =
            static_cast<uint8_t>(std::stoi(fd.pProtocolID, nullptr, 16));

        // need dummy pointer for strtoll() reference parameter
        char* pEnd {};
        fd.ipAddress =
            static_cast<uint32_t>(std::strtoll(fd.pIPAddress, &pEnd, 16));


        // add song line to map
        if (fd.ipAddress == MY_IP_ADDRESS && fd.protocolID == PROTOCOL_ID_TUNES)
        {
            // std::string's copy constructor creates song line string for map 
            std::string strSongLine { pLine };
            songMap.insert({ fd.seqno, strSongLine });
        }
    }
    // done with file
    input.close();
}

//------------------------------------------------------------------------------
// display song lines in map
//------------------------------------------------------------------------------
void displaySongLines(std::map<uint32_t, std::string>& songMap)
{
    // display song lines in order 
    for (auto& kv : songMap)
    {
        std::cout << kv.second << "\n";
    }
}
