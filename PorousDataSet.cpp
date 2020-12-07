#include "PorousDataSet.h"
#include "InputFile.h"
#include <stdio.h>
#include <gtest/gtest.h>
using namespace H5;

PorousDataSet::PorousDataSet(H5File& parent, int length, int image_dimension) : m_imagedim(image_dimension) {
    const hsize_t scaldim[1]={length};
    m_energyspace=DataSpace(1,scaldim);

    uint8_t fillval=0;
    DSetCreatPropList plist;
    plist.setFillValue(PredType::NATIVE_UINT8,&fillval);

    const hsize_t image_dim[3] = {length,image_dimension,image_dimension};
    m_imagespace=DataSpace(3,image_dim);

    m_imagedata=DataSet(parent.createDataSet("images",PredType::NATIVE_UINT8,m_imagespace,plist));
    m_energydata = DataSet(parent.createDataSet("energy",PredType::NATIVE_DOUBLE,m_energyspace));
}

void PorousDataSet::addEntry(double energy) {
    try{
    m_index=0;    
    hsize_t img_start[3] = {m_index,0,0};
    hsize_t img_size[3] = {1,m_imagedim,m_imagedim};
    hsize_t energy_start[1] = {m_index};
    hsize_t energy_count[1] = {1};

    m_energyspace.selectHyperslab(H5S_SELECT_SET,energy_count,energy_start);
    m_imagespace.selectHyperslab(H5S_SELECT_SET,img_size,img_start);
    
    m_energydata.write(&energy,PredType::NATIVE_DOUBLE,DataSpace::ALL,m_energyspace);//crash here
    m_imagedata.write(m_buffer,PredType::NATIVE_UINT8,DataSpace::ALL,m_imagespace);

    m_index++;
    }
       catch( FileIException error )
   {
    error.printErrorStack();
   }
   catch( DataSetIException error )
   {
    error.printErrorStack();
   }
   catch( DataSpaceIException error )
   {
    error.printErrorStack();
   }
}

void PorousDataSet::setBuffer(uint8_t* buf) {
    m_buffer=buf;
}

TEST(TestDataset,empty) {
    H5File ftest("../empty.h5",H5F_ACC_TRUNC);
    PorousDataSet d(ftest,20,400);
}

TEST(TestDataset,debugfunc) {
    H5File ftest("../out_test.h5",H5F_ACC_TRUNC);

    PorousDataSet d(ftest,100,10);

    for (int i = 0; i < 100; i++) {
        double a = (i+10)*(0.2);
        d.debugEntry(a,i);
    }
}

TEST(TestDataset,nameidk) {
    int test_size=400;
    uint8_t* buf = new uint8_t[test_size*test_size];

    for (int i = 0; i < test_size; i++) {
        for (int j = 0; j < test_size; j++) {
            if (i % 2 == j % 2) {buf[i*test_size+j]=255;}else{
                buf[i*test_size+j]=0;
            }
        }
    }
    double energy=1234.0;

    H5File ftest("../out_test.h5",H5F_ACC_TRUNC);

    PorousDataSet d(ftest,2,test_size);
    d.setBuffer(buf);
    d.addEntry(energy);
//    double two=91398894.0;
//    d.addEntry(two);
    delete[] buf;
}