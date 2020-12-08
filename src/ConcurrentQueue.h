#pragma once
#include <atomic>
#include <queue>
#include <thread>
#include "utility.h"
class ConcurrentQueue {
    private:
        std::queue<porous::InputData> m_queue;//push,pop
        std::atomic_int m_idxread{0};
        std::atomic_int m_idxmax{0};
        std::atomic_bool m_finished{false};
    public:
        ConcurrentQueue();
        void enqueue(porous::InputData const& item);
        std::vector<porous::InputData> dequeue_available();
        void finish();
        bool isFinished();
        int currentSize();
};