#include "concurrent_queue.h"


using namespace porous;
using namespace std;

template<typename T>
bool ConcurrentQueue<T>::isFinished() {
    return m_finished.load();
}
template<typename T>
void ConcurrentQueue<T>::finish() {
    m_finished.store(true);
}
template<typename T>
void ConcurrentQueue<T>::write(const T& val) {
    //m_vector.push_back(val);
    m_write++;
}
template<typename T>
T ConcurrentQueue<T>::read() {
    const int idx=m_read.load();
    m_read++;
    //return std::move(m_vector.begin()+idx);
    //return m_vector[idx];
}