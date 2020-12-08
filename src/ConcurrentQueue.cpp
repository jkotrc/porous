#include "ConcurrentQueue.h"
#include <gtest/gtest.h>
#include <iostream>

#include <cassert>

using namespace porous;
ConcurrentQueue::ConcurrentQueue() {

}
void ConcurrentQueue::enqueue(porous::InputData const& item) {
    m_queue.push(item);
    m_idxmax++;
}
std::vector<InputData> ConcurrentQueue::dequeue_available() {
    std::vector<InputData> available;
    while (m_idxread < m_idxmax) {
        available.push_back(m_queue.front());
        m_queue.pop();
        m_idxread++;
    }
    return available;
}
void ConcurrentQueue::finish() {
    m_finished.store(true);
    const bool fin = m_finished.load();
    assert(fin == true);
}
bool ConcurrentQueue::isFinished() {
    const bool fin = m_finished.load();
    return fin;
}
int ConcurrentQueue::currentSize() {
    return m_queue.size();
}

/*
expect -- continue test regardless
assert -- stop and fail test

ASSERT_EQ(x.length(),y.length) << "vectors x and y are of inequal length!!";
ASSERT_TRUE
GT,LT,GE,LE
*/
TEST(ConcQueue, DISABLED_BasicOperations) {
    InputData dat;
    dat.energy=1.0;
    std::vector<double2> pos;
    pos.push_back({1.0,2.0});

    ConcurrentQueue q;
    for (int i = 0; i < 5; i++) {
        q.enqueue(dat);
    }
    ASSERT_EQ(q.currentSize(), 5);
    std::vector<InputData> res = q.dequeue_available();
    ASSERT_EQ(res.size(),(size_t)5);
}

TEST(ConcQueue, ThreadSafety) {
    InputData dat;
    dat.energy=1.0;


}