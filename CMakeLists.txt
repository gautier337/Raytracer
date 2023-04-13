cmake_minimum_required(VERSION 3.0)
project(raytracer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

include_directories(
        Core/include
        Math/Factories/include
        Math/include
        Math/Vectors/include
)

set(EXECUTABLE_NAME "raytracer")
set(MATH_DIRECTORY Math/)

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
        Vectors/src/Vector3D.cpp
)

set(CMAKE_CPP_FLAGS "-Wall -Wextra -Werror -fno-gnu-unique")

# Transform all paths to absolute paths
list(TRANSFORM SRC_MAIN PREPEND ${CORE_DIRECTORY})
list(TRANSFORM SRC_CORE PREPEND ${CORE_DIRECTORY})
list(TRANSFORM SRC_MATH PREPEND ${MATH_DIRECTORY})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

add_executable(${EXECUTABLE_NAME} ${SRC_MAIN} ${SRC_CORE} ${SRC_MATH})

target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS})
