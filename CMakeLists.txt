cmake_minimum_required(VERSION 3.24)
project(SoundProcessor)

set(CMAKE_CXX_STANDARD 17)

add_executable(SoundProcessor main.cpp SoundProcessor.cpp SoundProcessor.h ConfigParser.cpp ConfigParser.h ConfigParser.h Converters.cpp Converters.h WAVParser.cpp WAVParser.h WAVWriter.cpp WAVWriter.h)
