cmake_minimum_required(VERSION 3.30)
project(signal_generator)

include_directories("C:/Users/xboxa/CLionProjects/signal_generator/fftw-3.3.5-dll64"
                    "C:/Users/xboxa/CLionProjects/signal_generator/libs")

set(CMAKE_CXX_STANDARD 20)

add_executable(signal_generator
        main.cpp)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

target_link_libraries(signal_generator PRIVATE
        "C:/Users/xboxa/CLionProjects/signal_generator/fftw-3.3.5-dll64/libfftw3-3.dll.a" # Double precision complex
        "C:/Users/xboxa/CLionProjects/signal_generator/fftw-3.3.5-dll64/libfftw3f-3.dll.a" # Single precision real
        "C:/Users/xboxa/CLionProjects/signal_generator/fftw-3.3.5-dll64/libfftw3l-3.dll.a" # Double precision real
        PRIVATE SFML::Graphics
)
