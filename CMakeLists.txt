cmake_minimum_required(VERSION 3.28)
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
        src/game_objects/Player.cpp
        src/game_objects/GameObject.cpp
        src/collisions/Collider.cpp
        src/collisions/ConvexPart.cpp
        src/collisions/GJK.cpp
        src/rendering/Renderer.cpp
        src/rendering/Texture.cpp
        src/rendering/Shader.cpp
        src/rendering/Mesh.cpp
        src/rendering/Model.cpp
        src/resources/FileIO.cpp
        src/resources/AssetManager.cpp
        src/terrain/Generator.cpp
        src/terrain/Noise.cpp
        src/terrain/ChunkPart.cpp
)

add_executable(game main.cpp ${SOURCES} ${HEADERS})
target_include_directories(game PRIVATE include)
target_link_libraries(game ${LIBRARIES})

enable_testing()

add_executable(tests tests.cpp ${SOURCES} ${HEADERS})
target_link_directories(tests PRIVATE include)
target_link_libraries(tests ${LIBRARIES})

include(GoogleTest)
gtest_discover_tests(tests)