#pragma once
#include <H5Cpp.h>
#include <thread>

#include <commonlib/utility.h>
#include <commonlib/ConcurrentQueue.h>
#include <commonlib/InputFile.h>

class ThreadedReader {
    private:
        std::vector<std::string> m_paths;
        std::shared_ptr<porous::ConcurrentQueue> m_queue;
        std::thread m_readthread;
    public:
        ThreadedReader(std::string path, std::shared_ptr<porous::ConcurrentQueue> queue);
        ThreadedReader(ThreadedReader const& cp);
        ~ThreadedReader();
        int getFileCount();
        std::shared_ptr<porous::ConcurrentQueue>& getQueue();
};