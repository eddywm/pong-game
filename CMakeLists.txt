cmake_minimum_required(VERSION 3.6)
project(pong-game)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_NAME "pong-game")
add_executable(${EXECUTABLE_NAME} main.cpp)



# Detect and add SFML
set(SFML_DIR "/home/eddylloyd/Documents/SFML-2.4.2/share/SFML/cmake/Modules")
set(CMAKE_MODULE_PATH "/home/eddylloyd/Documents/SFML-2.4.2/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()