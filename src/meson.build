project('calculator-converter',
  'c',
  'cpp',
  version: '0.1.0',
  default_options: [
    'cpp_std=c++20',
    'optimization=0',
    'debug=true'
  ]
)

executable(
  'calculator-converter',
  sources: [
    'lib/imgui_impl_glfw.cpp',
    'lib/imgui_impl_opengl3.cpp',
    'lib/imgui_stdlib.cpp',
    'lib/implot.cpp',
    'lib/implot_items.cpp',
    'lib/nml.c',
    'lib/nml_util.c',
    'conversion_functions.cpp',
    'conversion_gui.cpp',
    'graph_gui.cpp',
    'main.cpp',
    'maths_functions.cpp',
    'maths_gui.cpp',
    'scripting.cpp',
    'scripting_gui.cpp',
    'utils.cpp'
  ],
  dependencies: [
    dependency('imgui'),
    dependency('glfw3'),
    dependency('glew'),
    dependency('muparser'),
    dependency('rapidcsv'),
    dependency('toml11'),
    dependency('portable-file-dialogs')
  ],
  cpp_args: [
    '-Wno-deprecated-declarations'
  ]
)
