#include "Reader.h"

#include <commonlib/InputFile.h>

#include <gtest/gtest.h>

using namespace porous;
using std::string;
using std::unique_ptr;

namespace {
    constexpr int min(int x, int y) {
        return (x<y) ? x : y;
    }
    inline string getFileName(int N) {
        return std::to_string(N)+".h5";
    }
}

CudaReader::CudaReader(string input_path) : m_filecount(0), m_currentfile(0) {}

CudaReader::~CudaReader() {}

ImageSet CudaReader::nextN(int N) {
    ImageSet i;
    i.N=size_t{N};
    std::vector<double2> all_points;
    std::vector<int> breakpoints;
    std::vector<double> energies;
    for (;m_currentfile < min(N+m_currentfile,m_filecount); m_currentfile++) {
        InputFile f(getFileName(m_currentfile));
        energies.push_back(f.readEnergy());
        const std::vector<double2> pts = f.readPositions();
        all_points.insert(all_points.end(),pts.begin(),pts.end());
        breakpoints.push_back((int) all_points.size()-1);
    }
    i.positions = all_points;
    i.energies = energies;
    i.breakpoints = breakpoints;
    return i;
}

bool CudaReader::hasNext() {
    return (m_currentfile < m_filecount);
}

TEST(CudaReaderTest, reads_successfully) {
    InputFile in(getFileName(1));
    
}