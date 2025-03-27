from conan import ConanFile
from conan.tools.cmake import cmake_layout


class TerrainSimulation(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("opengl/system")
        self.requires("glad/0.1.36")
        self.requires("glfw/3.4")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.29]")

    def layout(self):
        cmake_layout(self)