#pragma once
#include <H5Cpp.h>

class PorousDataSet {
    private:
        int m_index{1};
        int m_imagedim;
        
        uint8_t* m_buffer;

        H5::DataSpace m_energyspace;
        H5::DataSet m_energydata;

        H5::DataSpace m_imagespace;
        H5::DataSet m_imagedata;
    public:
        PorousDataSet()=default;
        PorousDataSet(H5::H5File& parent, int length, int image_dimension);
        void addEntry(double energy,uint8_t* image);
        void addEntry(double energy);
        void setBuffer(uint8_t* buf);
        void debugEntry(double e, int idx);
};