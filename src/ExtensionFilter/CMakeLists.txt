find_package(yaml-cpp REQUIRED)


add_library(Filter src/Filter.cpp)

target_link_libraries(Filter yaml-cpp)

target_include_directories(Filter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})