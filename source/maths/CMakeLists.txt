include_directories (${CMAKE_SOURCE_DIR}/include)

file (GLOB MATHS_SOURCE "*.cpp")

add_library (MATHS ${MATHS_SOURCE})
