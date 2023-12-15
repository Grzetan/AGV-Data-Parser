cmake_minimum_required(VERSION 2.8)
project( AVL )
set(CMAKE_CXX_STANDARD 17)
set(EXE_NAME main)
set(PATH "./src")

set(SOURCE_FILES
    ${PATH}/pugixml.hpp
    ${PATH}/pugixml.cpp
    ${PATH}/converters/converter.h
    ${PATH}/converters/converter.cpp
    ${PATH}/converters/uint_converter.h
    ${PATH}/converters/uint_converter.cpp
    ${PATH}/converters/timestamp_converter.h
    ${PATH}/converters/timestamp_converter.cpp
    ${PATH}/utils.h
    ${PATH}/utils.cpp
)

add_executable( ${EXE_NAME} ${PATH}/parseBinary.cpp ${SOURCE_FILES} )