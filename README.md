# Build
```batch
 conan install . -sbuild_type=Debug -of=build/debug --build=missing 
 cmake -B build -DCMAKE_TOOLCHAIN_FILE="build/debug/build/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug
```