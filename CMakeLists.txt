cmake_minimum_required(VERSION 3.29)
project(terrain_simulation)

set(CMAKE_CXX_STANDARD 20)

include("cmake/build_mode.cmake")
include("cmake/os.cmake")
include("cmake/msvc.cmake")
include("cmake/conan.cmake")

include("${PROJECT_SOURCE_DIR}/cmake/conan_files/${ARCHIMEDES_BUILD_TYPE}/conan_toolchain.cmake")
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/conan_files/${ARCHIMEDES_BUILD_TYPE})

include_directories(${CMAKE_INCLUDE_PATH})

include("${PROJECT_SOURCE_DIR}/cmake/conan_files/${ARCHIMEDES_BUILD_TYPE}/conandeps_legacy.cmake")
list(APPEND LIBRARIES ${CONANDEPS_LEGACY})

set(SOURCES
        src/Application.cpp
)

set(HEADERS
        include/Application.h
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})