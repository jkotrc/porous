#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <iostream>

namespace porous {
    using std::chrono::high_resolution_clock;
    struct Timer {
        high_resolution_clock::time_point start;
        high_resolution_clock::time_point end;
        
        std::string message;
        Timer(std::string msg) {
            message=msg;
            start = high_resolution_clock::now();
        }
        int64_t timenow() {
            end = high_resolution_clock::now();
            int64_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
            return duration;
        }
        void now() {
            end = high_resolution_clock::now();
            int64_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
            std::cout << message << " took " << duration << "ms\n";
        }
        ~Timer() {
            end = high_resolution_clock::now();
            int64_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
            std::cout << message << " took " << duration << "ms\n";
        }

    };
    struct double2 {
        double x,y;
        double2 () : x(0),y(0){}
        double2 (const double xi, const double yi) : x(xi),y(yi){}
    };
    struct InputData {
        double energy;
        std::vector<double2> position;
        InputData(int n){position=std::vector<double2>(n);}
        InputData()=default;
    };
}