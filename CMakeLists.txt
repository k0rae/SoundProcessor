cmake_minimum_required(VERSION 3.24)
project(SoundProcessor)

set(CMAKE_CXX_STANDARD 17)

add_executable(SoundProcessor Converters.cpp Converters.h Factory.cpp Factory.h ConfigParser.cpp ConfigParser.h ConfigParser.h WAVParser.cpp WAVParser.h WAVWriter.cpp WAVWriter.h SoundProcessor.cpp SoundProcessor.h main.cpp)
