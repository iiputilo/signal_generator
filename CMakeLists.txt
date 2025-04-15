cmake_minimum_required(VERSION 3.30)
project(signal_generator)

include_directories("C:/Users/xboxa/CLionProjects/signal_generator/fftw-3.3.5-dll64")

set(CMAKE_CXX_STANDARD 20)

add_executable(signal_generator main.cpp)

target_link_libraries(signal_generator
        "C:/Users/xboxa/CLionProjects/signal_generator/fftw-3.3.5-dll64/libfftw3-3.dll.a" # Double precision complex
        "C:/Users/xboxa/CLionProjects/signal_generator/fftw-3.3.5-dll64/libfftw3f-3.dll.a" # Single precision real
        "C:/Users/xboxa/CLionProjects/signal_generator/fftw-3.3.5-dll64/libfftw3l-3.dll.a" # Double precision real
)