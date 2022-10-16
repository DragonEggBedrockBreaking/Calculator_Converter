from conans import ConanFile, Meson


class ConverterConan(ConanFile):
    name = "converter"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "pkg_config"
    requires = [
        "imgui/1.88",
        "glfw/3.3.8",
        "glew/2.2.0",
        "boost/1.80.0",
        "muparser/2.3.2",
        "fmt/9.1.0"
    ]

    def build(self):
        meson = Meson(self)
        meson.configure(
            source_folder="%s/src" %
            self.source_folder,
            build_folder="%s/dist" %
            self.source_folder)
        meson.build()
