cmake_minimum_required(VERSION 3.0.0)
project(FilTer VERSION 0.1.0)

set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

add_subdirectory(src/ExtensionFilter/)
#add_subdirectory(src/ConsoleGui/)





find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)
find_package(cxxopts REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(FileHandler src/FolderLocation/FileHandler.cpp)
add_library(Handler src/Handler/Handler.cpp)

add_executable(FilTer src/main.cpp)

target_link_libraries(FileHandler
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

target_link_libraries(Handler FileHandler Filter ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(FilTer Handler)
#target_link_libraries(FilTer ConsoleGui)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
