project('converter',
  'cpp',
  version: '0.1.0',
  default_options: [
    'cpp_std=c++20',
    'optimization=0',
    'debug=true'
  ]
)

executable(
  'converter',
  sources: [
    'lib/imgui_impl_glfw.cpp',
    'lib/imgui_impl_opengl3.cpp',
    'lib/imgui_stdlib.cpp',
    'main.cpp',
    'maths_functions.cpp'
  ],
  dependencies: [
    dependency('imgui'),
    dependency('glfw3'),
    dependency('glew'),
    dependency('boost')
  ]
)
