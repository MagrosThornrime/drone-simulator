from conan import ConanFile


class DroneSimulator(ConanFile):
    name = "Drone Simulator"
    settings = "build_type"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("opengl/system")
        self.requires("glad/0.1.36")
        self.requires("glm/1.0.1")
        self.requires("glfw/3.4")
        self.requires("assimp/5.4.3")
        self.requires("stb/cci.20230920")
        self.requires("jsoncpp/1.9.6")
        self.requires("gtest/1.16.0")


def build_requirements(self):
        self.tool_requires("cmake/[>=3.29]")