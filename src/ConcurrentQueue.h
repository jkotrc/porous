#pragma once
#include <atomic>
#include <queue>
#include <thread>
#include <exception>
#include <mutex>
#include "utility.h"

class QueueFullException : public std::exception {
    public:
    virtual const char* what() const throw() 
    {
        return "Attempted appending to full queue!";
    }
};

class ConcurrentQueue {
    private:
        porous::InputData* m_buffer;
        int m_size;//,m_front,m_rear;
        std::mutex m_mtx;
        int m_front;
        int m_rear;
        int m_currentsize;
        std::atomic_bool m_finished{false};
    public:
        ConcurrentQueue(int max_size);
        ConcurrentQueue();
        ~ConcurrentQueue();
        void enqueue(porous::InputData const& item);
        std::vector<porous::InputData> dequeue_available();
        void finish();
        bool isFinished();
        bool isFull();
        int currentSize();
};