from conan import ConanFile


class TerrainSimulation(ConanFile):
    name = "Terrain Simulation"
    settings = "build_type"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("opengl/system")
        self.requires("glad/0.1.36")
        self.requires("glfw/3.4")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.29]")