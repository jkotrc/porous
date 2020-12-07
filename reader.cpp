#include "reader.h"
#include "utility.h"
#include <iostream>

namespace fs = std::filesystem;
using namespace std;
using namespace porous;

namespace {
    std::vector<std::string> lst_directories(std::string const& dir_path) {
        vector<string> ret;
        Timer t("indexing files");
        for (auto& entry : fs::directory_iterator(dir_path)) {
            ret.push_back(entry.path().string());
        }
        cout << "There are " << ret.size() << " to read\n";
        return ret;
    }
    
    DataEntry readFile(string const& path) {
    H5File f;
    try{
        f = H5File(path, H5F_ACC_RDONLY);
    } catch(...) {
        cout << "this file did not read:\n" << path << endl;
        //return NULL;
    }
    DataSet coords_ds = f.openDataSet("coordinates");
    DataSpace coords_space = coords_ds.getSpace();
    hsize_t dims1[2];
    coords_space.getSimpleExtentDims(dims1,NULL);

    const int coord_dimension = (int)dims1[0];
    DataEntry entry(coord_dimension);
    const DataSet energy_ds = f.openDataSet("energy");
    energy_ds.read(&entry.energy, PredType::NATIVE_DOUBLE);

    hsize_t offset[2] = {0,1};
    hsize_t count[2] = {coord_dimension,2};
    coords_space.selectHyperslab(H5S_SELECT_SET,count,offset);
    
    hsize_t offset_output[2] = {0,0};
    hsize_t dim_output[2] = {coord_dimension,2};
    DataSpace output_space(2, dim_output);
    output_space.selectHyperslab(H5S_SELECT_SET,dim_output,offset_output);
    
    coords_ds.read(&entry.position[0], PredType::NATIVE_DOUBLE, output_space,coords_space);
    f.close();
    return entry;
}
    void threaded_read(atomic_int& counter, std::vector<DataEntry>& entries, vector<string> files) {
        for (int i = 0; i < files.size(); i++) {
            entries.push_back(readFile(files[i]));
            counter++;
        }
    }
}

void Reader::read(std::vector<DataEntry>& datae, std::string path) {
    vector<string> files = lst_directories(path);
    file_count = files.size();
    reader_thread = std::thread(threaded_read, std::ref(n_available),std::ref(datae),std::move(files));
}