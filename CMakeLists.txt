cmake_minimum_required (VERSION 3.15)
project (raytracer)

set (CMAKE_CXX_STANDARD 11)

add_subdirectory (source/maths)

#	Raytracer includes
include_directories (include)

#	External includes
include_directories (external/include/SDL2)
include_directories (external/include/PNG)

#	Get source code files
file (GLOB BRDF "source/brdf/*.cpp")
file (GLOB BTDF "source/btdf/*.cpp")
file (GLOB CAMERA "source/camera/*.cpp")
file (GLOB EVENT "source/event/*.cpp")
file (GLOB GEOMETRY "source/geometry/*.cpp")
file (GLOB IMAGE "source/image/*.cpp")
file (GLOB LIGHT "source/light/*.cpp")
file (GLOB MATERIAL "source/material/*.cpp")
file (GLOB RAYTRACER "source/raytracer/*.cpp")
file (GLOB SAMPLING "source/sampling/*.cpp")
file (GLOB SCENE "source/scene/*.cpp")
file (GLOB VIEWER "source/viewer/*.cpp")

#	Create executable files
add_executable (glossy "source/glossy_scene.cpp" ${BRDF} ${BTDF} ${CAMERA} ${EVENT} ${GEOMETRY} ${IMAGE} ${LIGHT} ${MATERIAL} ${RAYTRACER} ${SAMPLING} ${SCENE} ${VIEWER})
add_executable (recursive "source/recursive.cpp" ${BRDF} ${BTDF} ${CAMERA} ${EVENT} ${GEOMETRY} ${IMAGE} ${LIGHT} ${MATERIAL} ${RAYTRACER} ${SAMPLING} ${SCENE} ${VIEWER})
add_executable (arealight "source/arealight_scene.cpp" ${BRDF} ${BTDF} ${CAMERA} ${EVENT} ${GEOMETRY} ${IMAGE} ${LIGHT} ${MATERIAL} ${RAYTRACER} ${SAMPLING} ${SCENE} ${VIEWER})
add_executable (direct "source/first_scene.cpp" ${BRDF} ${BTDF} ${CAMERA} ${EVENT} ${GEOMETRY} ${IMAGE} ${LIGHT} ${MATERIAL} ${RAYTRACER} ${SAMPLING} ${SCENE} ${VIEWER})

#	Find external libraries
find_library (MINGWLIB mingw32 external/lib)
find_library (SDL_MAIN sdl2main external/lib)
find_library (SDL2 sdl2 external/lib)
find_library (PNG png15 external/lib)

#	Link libraries to executables
target_link_libraries (glossy LINK_PUBLIC ${MINGWLIB} ${SDL_MAIN} ${SDL2} ${PNG} MATHS)
target_link_libraries (recursive LINK_PUBLIC ${MINGWLIB} ${SDL_MAIN} ${SDL2} ${PNG} MATHS)
target_link_libraries (arealight LINK_PUBLIC ${MINGWLIB} ${SDL_MAIN} ${SDL2} ${PNG} MATHS)
target_link_libraries (direct LINK_PUBLIC ${MINGWLIB} ${SDL_MAIN} ${SDL2} ${PNG} MATHS)

#	Get dlls
file (GLOB DYNAMIC "dll/*.dll")

#	Install software
install (TARGETS glossy arealight direct recursive DESTINATION bin)
install (FILES ${DYNAMIC} DESTINATION bin)
install (DIRECTORY DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/renders")
