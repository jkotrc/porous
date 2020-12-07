#pragma once
#include <H5Cpp.h>
#include <thread>
#include "utility.h"
#include "ConcurrentQueue.h"
#include "InputFile.h"

//lstdirectories, readFile in an anonymous namespace
class Reader {
    private:
        std::vector<std::string> m_paths;
        ConcurrentQueue m_queue;
        std::thread m_readthread;
    public:
        Reader(std::string path);
        Reader(Reader const& cp);
        int getFileCount();
        void begin();
        //copy ctor
        ~Reader();
        std::vector<porous::InputData> get_available();
        bool isFinished();
};