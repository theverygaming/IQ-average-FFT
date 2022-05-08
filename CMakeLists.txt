cmake_minimum_required(VERSION 3.11)

project(iqaveragefft)

add_executable(iqaveragefft main.cpp)
find_package(PkgConfig)
pkg_check_modules(FFTW3 REQUIRED fftw3f)
pkg_check_modules(VOLK REQUIRED volk)
target_include_directories(iqaveragefft PUBLIC ${FFTW3_INCLUDE_DIRS} ${VOLK_INCLUDE_DIRS})
target_link_directories(iqaveragefft PUBLIC ${FFTW3_LIBRARY_DIRS} ${VOLK_LIBRARY_DIRS})
target_link_libraries(iqaveragefft PUBLIC ${FFTW3_LIBRARIES} ${VOLK_LIBRARIES})