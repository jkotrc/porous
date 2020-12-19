#include "ConcurrentQueue.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cassert>

using namespace porous;


ConcurrentQueue::ConcurrentQueue() : ConcurrentQueue(10) {}
ConcurrentQueue::ConcurrentQueue(int max_size) : m_size(max_size), m_rear(-1), m_front(0), m_currentsize(0) {
    m_buffer = new porous::InputData[m_size];
}
ConcurrentQueue::~ConcurrentQueue() {
    delete[] m_buffer;
}
bool ConcurrentQueue::enqueue(porous::InputData const& item) {
    std::lock_guard<std::mutex> lck(m_mtx);
    m_rear = (m_rear+1)%m_size;
    if (m_currentsize==m_size) {
        return false;
    }
    m_buffer[m_rear] = item;
    m_currentsize++;
    return true;
}

std::vector<InputData> ConcurrentQueue::dequeue_available() {
    std::lock_guard<std::mutex> lck(m_mtx);
    std::vector<InputData> available;
    while (m_currentsize > 0) {
        available.push_back(m_buffer[m_front]);
        m_front = (m_front+1)%m_size;
        m_currentsize--;
    }
    return available;
}
bool ConcurrentQueue::isFull() {
    return (m_rear+1 == m_front);
}
void ConcurrentQueue::finish() {
    m_finished.store(true);
}
bool ConcurrentQueue::isFinished() {
    const bool fin = m_finished.load();
    return fin;
}
int ConcurrentQueue::currentSize() {
    return m_currentsize;
}

/*TEST(ConcQueue, BasicOperations) {
    InputData dat;
    dat.energy=1.0;
    std::vector<double2> pos;
    pos.push_back({1.0,2.0});

    ConcurrentQueue q(4);

    for (int i = 0; i < 5; i++) {
        try {
         q.enqueue(dat);
        } catch(const QueueFullException& ex) {
            std::cout << ex.what() << std::endl;
            exception=true;
        }
    }
    ASSERT_TRUE(exception);
    ASSERT_EQ(q.currentSize(), 4);
    std::vector<InputData> res = q.dequeue_available();
    ASSERT_EQ(res.size(),(size_t)4);
}*/