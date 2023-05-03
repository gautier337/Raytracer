cmake_minimum_required(VERSION 3.0)
project(raytracer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

find_package(SFML 2.5
        COMPONENTS
        system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

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
set(LIGHTS_DIRECTORY RayTracer/Lights/src/)
set(SRC_LIGHTS
        DirectionalLight.cpp
        AmbientLight.cpp
        LightsFactory.cpp
)

# Math Sources
set(MATH_DIRECTORY RayTracer/Math/src/)
set(SRC_MATH
        MathFactory.cpp
        Point3D.cpp
        Vector3D.cpp
)

# Primitives Sources
set(PRIMITIVES_DIRECTORY RayTracer/Primitives/src/)
set(SRC_PRIMITIVES
        PrimitivesFactory.cpp
        Rectangle3D.cpp
        Sphere.cpp
        Plane.cpp
)

# Render Sources
set(RENDER_DIRECTORY RayTracer/Render/src/)
set(SRC_RENDER
        Color.cpp
        RenderFactory.cpp
)

# View Sources
set(VIEW_DIRECTORY RayTracer/View/src/)
set(SRC_VIEW
        Camera.cpp
        Ray.cpp
        ViewFactory.cpp
)

# Raytracer Sources
set(RAYTRACER_DIRECTORY RayTracer/src/)
set(SRC_RAYTRACER
        Scene.cpp
)

set(CMAKE_CPP_FLAGS "-Wall -Wextra -Werror -fno-gnu-unique")

# Transform all paths to absolute paths
list(TRANSFORM SRC_MAIN PREPEND ${CORE_DIRECTORY})
list(TRANSFORM SRC_CORE PREPEND ${CORE_DIRECTORY})
list(TRANSFORM SRC_LIGHTS PREPEND ${LIGHTS_DIRECTORY})
list(TRANSFORM SRC_MATH PREPEND ${MATH_DIRECTORY})
list(TRANSFORM SRC_PRIMITIVES PREPEND ${PRIMITIVES_DIRECTORY})
list(TRANSFORM SRC_RENDER PREPEND ${RENDER_DIRECTORY})
list(TRANSFORM SRC_VIEW PREPEND ${VIEW_DIRECTORY})
list(TRANSFORM SRC_RAYTRACER PREPEND ${RAYTRACER_DIRECTORY})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})


add_executable(
        ${EXECUTABLE_NAME}
        ${SRC_MAIN}
        ${SRC_CORE}
        ${SRC_MATH}
        ${SRC_LIGHTS}
        ${SRC_PRIMITIVES}
        ${SRC_RENDER}
        ${SRC_VIEW}
        ${SRC_RAYTRACER}
)

target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS} ${LIBCONFIG++_LIBRARIES})
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics)
