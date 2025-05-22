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
        src/game_objects/Player.cpp
        src/game_objects/GameObject.cpp
        src/game_objects/Terrain.cpp
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
        src/terrain/Chunk.cpp
)

set(HEADERS
        include/Application.h
        include/Logger.h
        include/game_objects/Player.h
        include/game_objects/GameObject.h
        include/game_objects/Terrain.h
        include/collisions/Collider.h
        include/collisions/ConvexPart.h
        include/collisions/GJK.h
        include/rendering/Texture.h
        include/rendering/Renderer.h
        include/rendering/Shader.h
        include/rendering/Mesh.h
        include/rendering/Model.h
        include/resources/FileIO.h
        include/resources/AssetManager.h
        include/resources/Image.h
        include/terrain/Generator.h
        include/terrain/Noise.h
        include/terrain/Chunk.h
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