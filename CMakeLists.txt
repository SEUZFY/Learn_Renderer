cmake_minimum_required (VERSION 3.8)

project ("Learn_Renderer")

add_definitions(
  -DDATA_PATH=\"${PROJECT_SOURCE_DIR}/data\"
)

add_executable (Learn_Renderer "src/tgaimage.cpp" "src/tgaimage.h" "src/main.cpp")

