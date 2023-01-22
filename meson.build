project('TSP', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

incdir = include_directories('imgui/backends', 'imgui')

glfw_lib = subproject('glfw').get_variable('glfw_dep')
gl = dependency('gl')

files = files(
  'src/main.cpp',
  'src/node.cpp',
  'src/path.cpp',
  'src/manager.cpp',
  'src/algs.cpp',
  'src/mst.cpp',
  'imgui/implot.cpp',
  'imgui/implot.cpp',
  'imgui/implot_items.cpp',
  'imgui/imgui.cpp',
  'imgui/imgui_draw.cpp',
  'imgui/imgui_tables.cpp',
  'imgui/imgui_demo.cpp',
  'imgui/imgui_widgets.cpp',
  'imgui/backends/imgui_impl_glfw.cpp',
  'imgui/backends/imgui_impl_opengl3.cpp',
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