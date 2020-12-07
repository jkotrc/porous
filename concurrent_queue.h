#pragma once
#include <atomic>
#include <vector>

namespace porous {
    template<typename T> class ConcurrentQueue {
        private:
            std::atomic_int m_read;
            std::atomic_int m_write;
            std::atomic_bool m_finished{false};
        public:
            bool isFinished();
            void write(const T& val);
            T read();
            void finish();
    };
}