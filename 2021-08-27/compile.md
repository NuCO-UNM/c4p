# MacOS
c++ -O3 -Wall -shared -std=c++14 -undefined dynamic_lookup $(python3 -m pybind11 --includes) mystat.cpp -o mystat_cpp$(python3-config --extension-suffix)
c++ -O3 -Wall -shared -std=c++14 -undefined dynamic_lookup $(python3 -m pybind11 --includes) mystat_simd.cpp -o mystat_simd$(python3-config --extension-suffix) -Xpreprocessor -fopenmp
c++ -O3 -Wall -shared -std=c++14 -undefined dynamic_lookup $(python3 -m pybind11 --includes) mystat_omp.cpp -o mystat_omp$(python3-config --extension-suffix) -Xpreprocessor -fopenmp

# Linux
c++ -O3 -Wall -shared -fPIC -std=c++14  $(python3 -m pybind11 --includes) mystat.cpp -o mystat_cpp$(python3-config --extension-suffix)
c++ -O3 -Wall -shared -fPIC -std=c++14  $(python3 -m pybind11 --includes) mystat_simd.cpp -o mystat_simd$(python3-config --extension-suffix) -fopenmp -lgomp
c++ -O3 -Wall -shared -fPIC -std=c++14  $(python3 -m pybind11 --includes) mystat_omp.cpp -o mystat_omp$(python3-config --extension-suffix) -fopenmp -lgomp
