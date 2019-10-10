cmake_minimum_required(VERSION 3.0.0)
project(Test VERSION 0.1.0)

include(CTest)
enable_testing()


find_package(Boost COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(FileHandler src/FolderLocation/FileHandler.cpp
                        src/FileHolder/Holder.cpp)
add_executable(Test src/main.cpp)

target_link_libraries(FileHandler
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

target_link_libraries(Test FileHandler)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
