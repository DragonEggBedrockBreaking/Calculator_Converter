from conans import ConanFile, Meson


class CalculatorConverterConan(ConanFile):
    name = "calculator-converter"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "pkg_config"
    requires = [
        "imgui/1.88",
        "glfw/3.3.8",
        "glew/2.2.0",
        "muparser/2.3.2",
        "rapidcsv/8.64",
        "toml11/3.7.1",
        "portable-file-dialogs/0.1.0"
    ]

    def build(self):
        meson = Meson(self)
        meson.configure(
            source_folder="%s/src" %
            self.source_folder,
            build_folder="%s/dist" %
            self.source_folder)
        meson.build()
