#include "processor.h"
#include "utility.h"

#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>

using namespace std;
using namespace porous;

#define SQ(a) (a*a)

#define Zi 6//atomic number
#define GAMMA 0.2 //0.2Angstrom = Carbon width of potential well
namespace {
    inline float V(const DataEntry& entry, const float x, const float y) {
        float ret=0;
        for (const double2& point : entry.position) {
            ret += exp(- (  SQ(x-point.x)+SQ(y-point.y)  )/(2*SQ(GAMMA)));
        }
        ret*=Zi;
        return ret;
    }
    inline void selectImage(h5data_t& dat,int index, int image_dimension) {
        hsize_t offset[3]={index,0,0};
        hsize_t count[3]={1,image_dimension,image_dimension};
        dat.first.selectHyperslab(H5S_SELECT_SET,count,offset);
    }
}

OutputFile::OutputFile(string name, int dim, int n_entries) : m_dimensions(dim), m_entrycount(n_entries) {
    m_file = H5File(name, H5F_ACC_TRUNC);

    const hsize_t scaldim[1] = {n_entries};
    m_energy.first=DataSpace (1,scaldim);

    uint8_t fillvalue=0;
    DSetCreatPropList plist;
    plist.setFillValue(PredType::NATIVE_UINT8,&fillvalue);

    const hsize_t posdim[3] = {n_entries,m_dimensions,m_dimensions};
    image = new float[m_dimensions*m_dimensions];
    
    m_positions.first=DataSpace(3,posdim);

    m_positions.second = DataSet(m_file.createDataSet("images",PredType::NATIVE_UINT8,m_positions.first,plist));
    m_energy.second = DataSet(m_file.createDataSet("energy",PredType::NATIVE_DOUBLE,m_energy.first));
}

OutputFile::~OutputFile() {
    if (!m_saved) {
        save();
    }
    delete[] image;
}

void OutputFile::setEnergy(const float e) {
    m_energy=e;
}

void OutputFile::addEntry(DataEntry&& entry) {
    if(m_entryindex >= m_entrycount) {
        cout << "entry index bigger than entry count!\n";
        throw std::exception();
    }

    const float dimension_scaler = m_dimensions/30;
    
    for (int i = 0; i < m_dimensions; i++) {
        for (int j = 0; j < m_dimensions; j++) {
            image[m_dimensions*j+i] = V(entry,dimension_scaler*i,dimension_scaler*j);
        }
    }

    //m_positions.write(image,PredType::NATIVE_FLOAT,)
    //m_energy.write(en)
    entry.energy=-1.0;
}

void OutputFile::save() {

    m_saved=true;
}

TEST(HDF5, SomeDots) {
    OutputFile f("ex.h5",100,2);
    DataEntry center;
    center.energy=123.0;
    center.position.push_back({0,0});
    DataEntry off;
    off.energy=345.0;
    off.position.push_back({20,0});
    f.addEntry(std::move(center));
    f.addEntry(std::move(off));
}