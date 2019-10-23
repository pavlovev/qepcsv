cmake_minimum_required(VERSION 3.5)

project(QEpCSV LANGUAGES CXX)

enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Test REQUIRED)

add_library(QEpCSV
  QEpCSV
  QEpCSV.h
  QEpCSV_global.h
  QEpCSVReader.cpp
  QEpCSVReader.h
)

target_link_libraries(QEpCSV PRIVATE Qt5::Core)
target_compile_definitions(QEpCSV PRIVATE QEPCSV_LIBRARY)

add_executable(Test_QEpCSV Test_QEpCSV.h)
target_link_libraries(Test_QEpCSV Qt5::Test QEpCSV)
target_compile_definitions(Test_QEpCSV PRIVATE TEST_DATA_FILENAME="${CMAKE_SOURCE_DIR}/test.csv")
add_test(Test_QEpCSV Test_QEpCSV)
