cmake_minimum_required(VERSION 2.8)

project(Imac3-MoteursPhysiques-PartyKel)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
#set(CMAKE_EXE_FLAGS "${CMAKE_EXE_FLAGS} -pg")

# Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} PartyKel/include third-party/AntTweakBar/include third-party/include include)

add_subdirectory(PartyKel)
add_subdirectory(third-party/AntTweakBar)

set(ALL_LIBRARIES PartyKel AntTweakBar ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} SDL_image)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(masse ${SRC_FILES} src/main.cpp)
target_link_libraries(masse ${ALL_LIBRARIES})