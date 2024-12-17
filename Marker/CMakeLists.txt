cmake_minimum_required (VERSION 3.8)

add_library (Marker STATIC marker.cpp)

target_include_directories(Marker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})