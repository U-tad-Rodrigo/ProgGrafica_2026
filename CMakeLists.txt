cmake_minimum_required(VERSION 3.16)
project(ProgGrafica_2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================
# DIRECTORIOS DE INCLUSIÓN Y LIBRERÍAS EXTERNAS
# ============================================================================
include_directories(
    ${CMAKE_SOURCE_DIR}/externalLibs/glad/inc
    ${CMAKE_SOURCE_DIR}/externalLibs/glfw/inc
    ${CMAKE_SOURCE_DIR}/externalLibs/glm/inc
)

link_directories(${CMAKE_SOURCE_DIR}/externalLibs/glfw/lib)

# ============================================================================
# PROYECTO: Hello Triangle
# ============================================================================
add_executable(MainClase
        ProgGrafica_2024/MainClase/main.cpp
        ProgGrafica_2024/MainClase/common.h
        ProgGrafica_2024/MainClase/EventManager.cpp
        ProgGrafica_2024/MainClase/EventManager.h
        ProgGrafica_2024/MainClase/Object3D.cpp
        ProgGrafica_2024/MainClase/Object3D.h
        ProgGrafica_2024/MainClase/libMath.cpp
        ProgGrafica_2024/MainClase/libMath.h
        ProgGrafica_2024/MainClase/Render.cpp
        ProgGrafica_2024/MainClase/Render.h
        ProgGrafica_2024/MainClase/Camera.cpp
        ProgGrafica_2024/MainClase/Camera.h
)
target_include_directories(MainClase PRIVATE ${CMAKE_SOURCE_DIR}/ProgGrafica_2024/MainClase)
target_link_libraries(MainClase glfw3 opengl32)

# ============================================================================
# PROYECTOS ADICIONALES (generados por nuevo_proyecto.bat)
# ============================================================================


# NUEVO_PROYECTO_AQUI
