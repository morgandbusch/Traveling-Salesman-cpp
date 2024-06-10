project('TSP', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17', 'c_std=c99'])

incdir = include_directories('libs/imgui/backends', 'libs/imgui', 'libs/implot')

cmake = import ('cmake')
cmake_glfw_opts = cmake.subproject_options()
cmake_glfw_opts.add_cmake_defines({'GLFW_BUILD_X11': true})
cmake_glfw_opts.add_cmake_defines({'GLFW_BUILD_WAYLAND': false})
cmake_glfw_opts.add_cmake_defines({'BUILD_SHARED_LIBS': false})
cmake_glfw_opts.append_compile_args('c', '-Wunused-parameter')

cmake_glfw = cmake.subproject('glfw', options: cmake_glfw_opts)

glfw_lib = subproject('glfw').get_variable('glfw_dep')
gl = dependency('gl')

files = files(
  'src/main.cpp',
  'src/node.cpp',
  'src/path.cpp',
  'src/manager.cpp',
  'src/algs.cpp',
  'src/mst.cpp',
  'libs/imgui/imgui.cpp',
  'libs/imgui/imgui_draw.cpp',
  'libs/imgui/imgui_tables.cpp',
  'libs/imgui/imgui_demo.cpp',
  'libs/imgui/imgui_widgets.cpp',
  'libs/imgui/backends/imgui_impl_glfw.cpp',
  'libs/imgui/backends/imgui_impl_opengl3.cpp',
  'libs/implot/implot.cpp',
  'libs/implot/implot.cpp',
  'libs/implot/implot_items.cpp',
)

executable('app',
           files,
           include_directories: incdir,
           dependencies: [glfw_lib, gl])


nodetest_files = files(
  'src/node_test.cpp',
  'src/node.cpp',
)

nodetest = executable('nodetest', nodetest_files)
test('node', nodetest)

pathtest_files = files(
  'src/path_test.cpp',
  'src/path.cpp',
  'src/node.cpp',
)

pathtest = executable('pathtest', pathtest_files)
test('path', pathtest)

msttest_files = files(
  'src/mst_test.cpp',
  'src/node.cpp',
  'src/mst.cpp',
)

msttest = executable('msttest', msttest_files)
test('mst', msttest)
