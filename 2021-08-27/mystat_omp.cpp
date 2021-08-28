/* mystat.cpp
Author: Huaiyu Duan (UNM)
Description: Python extension that computes the statistics.
*/ 
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <tuple>
#include <cmath>

// Compute the mean and standard deviation (std) of the data.
inline void mean_std(const double *const data, // data
    const int n, // size of the data
    double &mean, // average of the values
    double &std // standard deviation
) {
    mean = 0.;
    #pragma omp parallel for simd reduction(+: mean)
    for (int i = 0; i < n; ++i) {
        mean += data[i];
    }
    mean /= n;
    double sum = 0.;
    #pragma omp parallel for simd reduction(+: sum)
    for (int i = 0; i < n; ++i) {
        double diff = data[i] - mean;
        sum += diff * diff;
    }
    std = sqrt(sum / n);
}

// Compute the mean and standard deviation (std) of the data using the alternative formula.
inline void mean_std2(const double *const data, // data
    const int n, // size of the data
    double &mean, // average of the values
    double &std // standard deviation
) {
    mean = 0.;
    double sum = 0.;
    #pragma omp parallel for simd reduction(+: mean, sum)
    for (int i = 0; i < n; ++i) {
        double x = data[i];
        mean += x;
        sum += x * x;
    }
    mean /= n;
    std = sqrt(sum/n - mean*mean);
}

using nparray = // NumPy dense array
    pybind11::array_t<double, // double data type
        pybind11::array::c_style | // dense, row major array
        pybind11::array::forcecast>; // convert the array if necessary

// wrapper for mean_std
auto mean_std_wrapper(nparray data) {
    // size and pointer of the array
    int n = data.request().size;
    double *data_ptr = static_cast<double *>(data.request().ptr);
    double mean, std; // average and standard deviation
    mean_std(data_ptr, n, mean, std);

    return std::make_tuple(mean, std);
}

// wrapper for mean_std2
auto mean_std2_wrapper(nparray data) {
    // size and pointer of the array
    int n = data.request().size;
    double *data_ptr = static_cast<double *>(data.request().ptr);
    double mean, std; // average and standard deviation
    mean_std2(data_ptr, n, mean, std);

    return std::make_tuple(mean, std);
}

// expose the functions to Python
PYBIND11_MODULE(mystat_omp, // module name
    m // dummy variable representing the module
) {
    m.doc() = "C++ extension for computing the statistics."; // doc string for the module
    m.def("mean_std", // name of the function
        &mean_std_wrapper // pointer to the actual function
    );
    m.def("mean_std2", &mean_std2_wrapper);
}