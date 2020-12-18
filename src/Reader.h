#pragma once
#include <H5Cpp.h>
#include <thread>
#include "utility.h"
#include "ConcurrentQueue.h"
#include "InputFile.h"

class Reader {
    private:
        std::vector<std::string> m_paths;
        std::shared_ptr<ConcurrentQueue> m_queue;
        std::thread m_readthread;
    public:
        Reader(std::string path, std::shared_ptr<ConcurrentQueue> queue);
        Reader(Reader const& cp);
        ~Reader();
        int getFileCount();
        std::shared_ptr<ConcurrentQueue>& getQueue();
};