cmake_minimum_required(VERSION 3.0)
project(raytracer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

find_package(SFML 2.5
        COMPONENTS
        system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

include_directories(
        Core/include
        Math/Factories/include
        Math/include
        Math/Point3D/include
        Math/Vectors/include
        Raytracer/Ray/include
        Raytracer/Sphere/include
        Raytracer/Rectangle3D/include
        Raytracer/Camera/include
)

set(EXECUTABLE_NAME "raytracer")
set(MATH_DIRECTORY Math/)
set(RAYTRACER_DIRECTORY Raytracer/)

set(SRC_MAIN
        src/main.cpp
)

# Core Sources
set(CORE_DIRECTORY Core/)
set(SRC_CORE
        src/Raytracer.cpp
)

# Math Sources
set(MATH_DIRECTORY Math/)
set(SRC_MATH
        Factories/src/Factory.cpp
        Point3D/src/Point3D.cpp
        Vectors/src/Vector3D.cpp
)

# Raytracer Sources
set(RAYTRACER_DIRECTORY Raytracer/)
set(SRC_RAYTRACER
        Ray/src/Ray.cpp
        Sphere/src/Sphere.cpp
        Rectangle3D/src/Rectangle3D.cpp
        Camera/src/Camera.cpp
)

set(CMAKE_CPP_FLAGS "-Wall -Wextra -Werror -fno-gnu-unique")

# Transform all paths to absolute paths
list(TRANSFORM SRC_MAIN PREPEND ${CORE_DIRECTORY})
list(TRANSFORM SRC_CORE PREPEND ${CORE_DIRECTORY})
list(TRANSFORM SRC_MATH PREPEND ${MATH_DIRECTORY})
list(TRANSFORM SRC_RAYTRACER PREPEND ${RAYTRACER_DIRECTORY})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})


add_executable(${EXECUTABLE_NAME} ${SRC_MAIN} ${SRC_CORE} ${SRC_MATH} ${SRC_RAYTRACER})

target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS})
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics)
