cmake_minimum_required(VERSION 3.2)
project(birdDetector)

find_package(PkgConfig)

pkg_check_modules(SNDFILE REQUIRED IMPORTED_TARGET sndfile>=1.0.19)
pkg_check_modules(FFTW3 REQUIRED IMPORTED_TARGET fftw3>=0.15.0)
pkg_check_modules(CAIRO REQUIRED IMPORTED_TARGET cairo>=1.4.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -Wall -Wextra -lm")
add_compile_options(-lm)
add_executable(birdDetector spectrogram.c common.c spectrum.c window.c)
target_link_libraries(birdDetector
  PRIVATE
    PkgConfig::SNDFILE
    PkgConfig::FFTW3
    PkgConfig::CAIRO
	m
)
