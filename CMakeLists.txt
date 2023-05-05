cmake_minimum_required(VERSION 3.0)
project(raytracer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(OpenGL_GL_PREFERENCE GLVND)

# SFML Library
find_package(SFML 2.5
        COMPONENTS
        system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# OpenGL Library
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# libConfig library
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG++ REQUIRED libconfig++)
include_directories(${LIBCONFIG++_INCLUDE_DIRS})
link_directories(${LIBCONFIG++_LIBRARY_DIRS})

include_directories(
        Core/include
        ImGUI
        RayTracer/include
        RayTracer/Lights/include
        RayTracer/Math/include
        RayTracer/Primitives/include
        RayTracer/Render/include
        RayTracer/View/include
)

set(EXECUTABLE_NAME "raytracer")
set(RAYTRACER_DIRECTORY RayTracer/)

# Main Sources
set(SRC_MAIN
        src/main.cpp
)

# Core Sources
set(CORE_DIRECTORY Core/)
set(SRC_CORE
        src/RayTracer.cpp
        src/parse_config.cpp
)

# ImGUI Sources
set(IMGUI_DIRECTORY ImGUI/)
set(SRC_IMGUI
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        imgui-SFML.cpp
        imgui.cpp
)


# Lights Plugins
set(LIGHTS_DIRECTORY Lights/src/)
set(SRC_AMBIENT_LIGHT ${RAYTRACER_DIRECTORY}${LIGHTS_DIRECTORY}AmbientLight.cpp)
set(SRC_DIRECTIONAL_LIGHT ${RAYTRACER_DIRECTORY}${LIGHTS_DIRECTORY}DirectionalLight.cpp)

# Math Plugins
set(MATH_DIRECTORY Math/src/)
set(SRC_POINT3D ${RAYTRACER_DIRECTORY}${MATH_DIRECTORY}Point3D.cpp)
set(SRC_RECTANGLE3D ${RAYTRACER_DIRECTORY}${MATH_DIRECTORY}Rectangle3D.cpp)
set(SRC_VECTOR3D ${RAYTRACER_DIRECTORY}${MATH_DIRECTORY}Vector3D.cpp)

# Primitives Plugins
set(PRIMITIVES_DIRECTORY Primitives/src/)
set(SRC_CONE ${RAYTRACER_DIRECTORY}${PRIMITIVES_DIRECTORY}Cone.cpp)
set(SRC_PLANE ${RAYTRACER_DIRECTORY}${PRIMITIVES_DIRECTORY}Plane.cpp)
set(SRC_SPHERE ${RAYTRACER_DIRECTORY}${PRIMITIVES_DIRECTORY}Sphere.cpp)
set(SRC_CONE ${RAYTRACER_DIRECTORY}${PRIMITIVES_DIRECTORY}Cone.cpp)
set(SRC_CYLINDER ${RAYTRACER_DIRECTORY}${PRIMITIVES_DIRECTORY}Cylinder.cpp)

# Render Plugins
set(RENDER_DIRECTORY Render/src/)
set(SRC_COLOR ${RAYTRACER_DIRECTORY}${RENDER_DIRECTORY}Color.cpp)

# View Plugins
set(VIEW_DIRECTORY View/src/)
set(SRC_CAMERA ${RAYTRACER_DIRECTORY}${VIEW_DIRECTORY}Camera.cpp)
set(SRC_RAY ${RAYTRACER_DIRECTORY}${VIEW_DIRECTORY}Ray.cpp)

# Raytracer Sources
set(SOURCES_DIRECTORY src/)
set(SRC_RAYTRACER
        Factory.cpp
        Library.cpp
        Scene.cpp
)


# Set compiler flags
set(CMAKE_CPP_FLAGS "-Wall -Wextra -Werror -fno-gnu-unique")

# Transform all paths to absolute paths
list(TRANSFORM SRC_MAIN PREPEND ${CORE_DIRECTORY})
list(TRANSFORM SRC_CORE PREPEND ${CORE_DIRECTORY})
list(TRANSFORM SRC_IMGUI PREPEND ${IMGUI_DIRECTORY})
list(TRANSFORM SRC_RAYTRACER PREPEND ${RAYTRACER_DIRECTORY}/${SOURCES_DIRECTORY})

# Set plugins names
set(AMBIENT_LIGHT_LIB AmbientLight)
set(DIRECTIONAL_LIGHT_LIB DirectionalLight)

set(POINT3D_LIB Point3D)
set(RECTANGLE3D_LIB Rectangle3D)
set(VECTOR3D_LIB Vector3D)

set(CONE_LIB Cone)
set(PLANE_LIB Plane)
set(SPHERE_LIB Sphere)
set(CONE_LIB Cone)
set(CYLINDER_LIB Cylinder)

set(COLOR_LIB Color)

set(CAMERA_LIB Camera)
set(RAY_LIB Ray)


# Add plugins
add_library(${AMBIENT_LIGHT_LIB} SHARED ${SRC_AMBIENT_LIGHT})
add_library(${DIRECTIONAL_LIGHT_LIB} SHARED ${SRC_DIRECTIONAL_LIGHT})

add_library(${POINT3D_LIB} SHARED ${SRC_POINT3D})
add_library(${RECTANGLE3D_LIB} SHARED ${SRC_RECTANGLE3D})
add_library(${VECTOR3D_LIB} SHARED ${SRC_VECTOR3D})

add_library(${PLANE_LIB} SHARED ${SRC_PLANE})
add_library(${SPHERE_LIB} SHARED ${SRC_SPHERE})
add_library(${CONE_LIB} SHARED ${SRC_CONE})
add_library(${CYLINDER_LIB} SHARED ${SRC_CYLINDER})

add_library(${COLOR_LIB} SHARED ${SRC_COLOR})

add_library(${CAMERA_LIB} SHARED ${SRC_CAMERA})
add_library(${RAY_LIB} SHARED ${SRC_RAY})

# Set plugins output directory
set_target_properties(${AMBIENT_LIGHT_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/lights/)
set_target_properties(${DIRECTIONAL_LIGHT_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/lights/)

set_target_properties(${POINT3D_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/math/)
set_target_properties(${RECTANGLE3D_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/math/)
set_target_properties(${VECTOR3D_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/math/)

set_target_properties(${CONE_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/primitives/)
set_target_properties(${PLANE_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/primitives/)
set_target_properties(${SPHERE_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/primitives/)
set_target_properties(${CONE_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/primitives/)
set_target_properties(${CYLINDER_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/primitives/)

set_target_properties(${COLOR_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/render/)

set_target_properties(${CAMERA_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/view/)
set_target_properties(${RAY_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/plugins/view/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

add_executable(
        ${EXECUTABLE_NAME}
        ${SRC_MAIN}
        ${SRC_CORE}
        ${SRC_IMGUI}
        ${SRC_RAYTRACER}
)

target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS} ${LIBCONFIG++_LIBRARIES})
target_link_libraries(${EXECUTABLE_NAME} OpenGL::GL)
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics)

# Link plugins
target_link_libraries(${EXECUTABLE_NAME} ${AMBIENT_LIGHT_LIB})
target_link_libraries(${EXECUTABLE_NAME} ${DIRECTIONAL_LIGHT_LIB})

target_link_libraries(${EXECUTABLE_NAME} ${POINT3D_LIB})
target_link_libraries(${EXECUTABLE_NAME} ${RECTANGLE3D_LIB})
target_link_libraries(${EXECUTABLE_NAME} ${VECTOR3D_LIB})

target_link_libraries(${EXECUTABLE_NAME} ${CONE_LIB})
target_link_libraries(${EXECUTABLE_NAME} ${PLANE_LIB})
target_link_libraries(${EXECUTABLE_NAME} ${SPHERE_LIB})
target_link_libraries(${EXECUTABLE_NAME} ${CONE_LIB})
target_link_libraries(${EXECUTABLE_NAME} ${CYLINDER_LIB})

target_link_libraries(${EXECUTABLE_NAME} ${COLOR_LIB})

target_link_libraries(${EXECUTABLE_NAME} ${CAMERA_LIB})
target_link_libraries(${EXECUTABLE_NAME} ${RAY_LIB})
