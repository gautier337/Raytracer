cmake_minimum_required(VERSION 3.0)
project(raytracer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# SFML Library
find_package(SFML 2.5
        COMPONENTS
        system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# libConfig library
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG++ REQUIRED libconfig++)
include_directories(${LIBCONFIG++_INCLUDE_DIRS})
link_directories(${LIBCONFIG++_LIBRARY_DIRS})

include_directories(
        Core/include
        Core/DLLoader/include
        Raytracer/Scene/include
        RayTracer/include
        RayTracer/Lights/include
        RayTracer/Math/include
        RayTracer/Primitives/include
        RayTracer/Render/include
        RayTracer/View/include
)

set(EXECUTABLE_NAME "raytracer")
set(RAYTRACER_DIRECTORY RayTracer/)

set(SRC_MAIN
        src/main.cpp
)

# Core Sources
set(CORE_DIRECTORY Core/)
set(SRC_CORE
        DLLoader/src/DLLoader.cpp
        src/RayTracer.cpp
        src/parse_config.cpp
)

# Lights Sources
set(LIGHTS_DIRECTORY Lights/src/)
set(SRC_LIGHTS
        DirectionalLight.cpp
        LightsFactory.cpp
)

# Math Sources
set(MATH_DIRECTORY Math/src/)
set(SRC_MATH
        MathFactory.cpp
        Point3D.cpp
        Vector3D.cpp
)

# Primitives Sources
set(PRIMITIVES_DIRECTORY Primitives/src/)
set(SRC_PRIMITIVES
        PrimitivesFactory.cpp
        Rectangle3D.cpp
        Sphere.cpp
)

# Render Sources
set(RENDER_DIRECTORY Render/src/)
set(SRC_RENDER
        Color.cpp
        RenderFactory.cpp
)

# View Sources
set(VIEW_DIRECTORY View/src/)
set(SRC_VIEW
        Camera.cpp
        Ray.cpp
        ViewFactory.cpp
)

# Raytracer Sources
set(SOURCES_DIRECTORY src/)
set(SRC_RAYTRACER
        Scene.cpp
)

set(CMAKE_CPP_FLAGS "-Wall -Wextra -Werror -fno-gnu-unique")

# Transform all paths to absolute paths
list(TRANSFORM SRC_MAIN PREPEND ${CORE_DIRECTORY})
list(TRANSFORM SRC_CORE PREPEND ${CORE_DIRECTORY})
list(TRANSFORM SRC_RAYTRACER PREPEND ${RAYTRACER_DIRECTORY}/${SOURCES_DIRECTORY})

# Absolute plugins paths
list(TRANSFORM SRC_LIGHTS PREPEND ${RAYTRACER_DIRECTORY}/${LIGHTS_DIRECTORY})
list(TRANSFORM SRC_MATH PREPEND ${RAYTRACER_DIRECTORY}/${MATH_DIRECTORY})
list(TRANSFORM SRC_PRIMITIVES PREPEND ${RAYTRACER_DIRECTORY}/${PRIMITIVES_DIRECTORY})
list(TRANSFORM SRC_RENDER PREPEND ${RAYTRACER_DIRECTORY}/${RENDER_DIRECTORY})
list(TRANSFORM SRC_VIEW PREPEND ${RAYTRACER_DIRECTORY}/${VIEW_DIRECTORY})

# Plugins
set(LIGHTS_LIB raytracer_lights)
set(MATH_LIB raytracer_math)
set(PRIMITIVES_LIB raytracer_primitives)
set(RENDER_LIB raytracer_render)
set(VIEW_LIB raytracer_view)

add_library(${LIGHTS_LIB} SHARED ${SRC_LIGHTS})
add_library(${MATH_LIB} SHARED ${SRC_MATH})
add_library(${PRIMITIVES_LIB} SHARED ${SRC_PRIMITIVES})
add_library(${RENDER_LIB} SHARED ${SRC_RENDER})
add_library(${VIEW_LIB} SHARED ${SRC_VIEW})

set_target_properties(${LIGHTS_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/)
set_target_properties(${MATH_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/)
set_target_properties(${PRIMITIVES_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/)
set_target_properties(${RENDER_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/)
set_target_properties(${VIEW_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

add_executable(
        ${EXECUTABLE_NAME}
        ${SRC_MAIN}
        ${SRC_CORE}
        ${SRC_RAYTRACER}
)

target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS} ${LIBCONFIG++_LIBRARIES})
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics)
