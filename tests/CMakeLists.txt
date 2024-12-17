
set(BOOST_ROOT "D:/IT/WIN32API/OS_Lab3/boost_1_87_0")
set(BOOST_INCLUDEDIR "D:/IT/WIN32API/OS_Lab3/boost_1_87_0")
 set(BOOST_LIBRARYDIR "D:/IT/WIN32API/OS_Lab3/boost_1_87_0/stage/lib")

find_package(Boost 1.87.0 REQUIRED COMPONENTS unit_test_framework)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

add_executable(MarkerTests marker_test.cpp)
target_link_libraries(MarkerTests ${BOOST_LIBRARIES})

target_include_directories(MarkerTests PRIVATE ${CMAKE_SOURCE_DIR}/Marker ${CMAKE_SOURCE_DIR}/include)

add_test(MarkerTests MarkerTests)