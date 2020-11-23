#include "utility.h"
#include <stdlib.h>
#include <cstring>

#define STARTING_SIZE 10*sizeof(double)
using namespace porous;
using namespace std;

typedef vector<byte>::iterator buffer_iter;

DataBuffer::DataBuffer(int n_entries) : n_entries(n_entries) {
    
}

DataBuffer::~DataBuffer() {
    delete[] &_buffer; //TODO: does this work?
}

//structure: energy, N, double array
void DataBuffer::add(DataEntry& entry) {
    const size_t bigness = (entry.position_length+1)*sizeof(double)+sizeof(int);
    buffer_iter cursor = _buffer.end();
    _buffer.resize(_buffer.size()+bigness);
    
    byte* energy = reinterpret_cast<byte*>(&entry);
    std::copy(energy, energy+sizeof(double),cursor);
    cursor+=sizeof(double);
    
    byte* number = reinterpret_cast<byte*>(&entry.position_length);
    std::copy(number, number+sizeof(int), cursor);
    cursor+=sizeof(int);

    byte* positions = reinterpret_cast<byte*>(&entry.position);
    std::copy(positions, positions+entry.position_length*sizeof(double3), cursor);
    n_entries++;
}

/*
something like a while loop in the appendor thread that ends when current==maxsize
and continues if null is received
*/
DataEntry* DataBuffer::next() {
    if (current >= n_entries) return NULL;

    buffer_iter cursor = _buffer.begin()+current;
    DataEntry* ret = new DataEntry;
    std::memcpy(&ret->energy, cursor.base(), sizeof(double));
    cursor+=sizeof(double);
    std::memcpy(&ret->position_length, cursor.base(), sizeof(int));
    cursor+=sizeof(int);
    std::memcpy(&ret->position, cursor.base(), ret->position_length*sizeof(double3));
    current++;
    return ret;
}