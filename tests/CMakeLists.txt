
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

add_executable(MarkerTests marker_test.cpp)
target_link_libraries(MarkerTests ${BOOST_LIBRARIES})

target_include_directories(MarkerTests PRIVATE ${CMAKE_SOURCE_DIR}/Marker ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/boost_1_87_0)

add_test(MarkerTests MarkerTests)