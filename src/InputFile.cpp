#include "InputFile.h"

#include <gtest/gtest.h>
#include <cmath>

using namespace porous;
using namespace H5;

InputFile::InputFile(std::string const& path) : H5File(path,H5F_ACC_RDONLY) {
    
}
InputFile::~InputFile() {
    this->close();
}

double InputFile::readEnergy() {
    const DataSet ds = this->openDataSet("energy");
    double energy;
    ds.read(&energy, PredType::NATIVE_DOUBLE);
    return energy;
}

std::vector<double2> InputFile::readPositions() {
    std::vector<double2> positions;
    const DataSet ds = this->openDataSet("coordinates");
    DataSpace space = ds.getSpace();
    hsize_t dims[2];
    space.getSimpleExtentDims(dims,NULL);

    hsize_t offset[2] = {0,1};
    hsize_t count[2] = {dims[0],2};
    space.selectHyperslab(H5S_SELECT_SET,count,offset);

    hsize_t offset_output[2] = {0,0};
    hsize_t dim_output[2] = {dims[0],2};
    DataSpace output_space(2, dim_output);
    output_space.selectHyperslab(H5S_SELECT_SET,dim_output,offset_output);

    positions.resize(dims[0]);
    ds.read(&positions[0], PredType::NATIVE_DOUBLE,output_space,space);
    return positions;
}

TEST(TestInputFile, ReadTest) {
    //energy is -3282.62
    //there are 368 points
    //the 10th one is non-zero
    InputFile t("../samples/sample.h5");
    
    ASSERT_DOUBLE_EQ(round(t.readEnergy()), round(-3282.62));
    std::vector<double2> pos = t.readPositions();
    ASSERT_GE(pos[10].x,0);
    ASSERT_EQ((int)pos.size(),368);
}