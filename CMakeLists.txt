cmake_minimum_required(VERSION 3.29)
project(drone_simulator)

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
        src/Logger.cpp
        src/Camera.cpp
        src/rendering/Renderer.cpp
        src/rendering/Texture.cpp
        src/rendering/Shader.cpp
        src/rendering/Mesh.cpp
        src/rendering/Model.cpp
        src/resources/FileIO.cpp
        src/resources/AssetManager.cpp
        src/resources/Image.cpp
)

set(HEADERS
        include/Application.h
        include/Logger.h
        include/Camera.h
        include/rendering/Texture.h
        include/rendering/Renderer.h
        include/rendering/Shader.h
        include/rendering/Mesh.h
        include/rendering/Model.h
        include/resources/FileIO.h
        include/resources/AssetManager.h
        include/resources/Image.h
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})