cmake_minimum_required(VERSION 2.8)
project( 3D-Drone-Reconstruction )
set(CMAKE_CXX_STANDARD 17)
set(EXE_NAME main)
set(PATH "./src")

set(SOURCE_FILES
    ${PATH}/pugixml.hpp
    ${PATH}/pugixml.cpp
    ${PATH}/converters/converter.h
    ${PATH}/converters/converter.cpp
)

add_executable( ${EXE_NAME} ${PATH}/parseBinary.cpp ${SOURCE_FILES} )

# add_custom_command(TARGET ${EXE_NAME}
#                    COMMAND ${EXE_NAME}
#                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#                    COMMENT "Running ${EXE_NAME}")