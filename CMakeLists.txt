cmake_minimum_required(VERSION 3.16)
project(ProgGrafica_2024)

set(CMAKE_CXX_STANDARD 20)
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
        ProgGrafica_2024/MainClase/common.h
        ProgGrafica_2024/MainClase/MainPRGR_2024.cpp
        ProgGrafica_2024/MainClase/EventManager.cpp
        ProgGrafica_2024/MainClase/EventManager.h
        ProgGrafica_2024/MainClase/Object3D.cpp
        ProgGrafica_2024/MainClase/Object3D.h
        ProgGrafica_2024/MainClase/Luz.cpp
        ProgGrafica_2024/MainClase/Luz.h
        ProgGrafica_2024/MainClase/Material.cpp
        ProgGrafica_2024/MainClase/Material.h
        ProgGrafica_2024/MainClase/libMath.cpp
        ProgGrafica_2024/MainClase/libMath.h
        ProgGrafica_2024/MainClase/Render.cpp
        ProgGrafica_2024/MainClase/Render.h
        ProgGrafica_2024/MainClase/Camera.cpp
        ProgGrafica_2024/MainClase/Camera.h
        ProgGrafica_2024/MainClase/Shader.cpp
        ProgGrafica_2024/MainClase/Shader.h
        ProgGrafica_2024/MainClase/Texture.h
        ProgGrafica_2024/MainClase/Texture.cpp
        ProgGrafica_2024/MainClase/System.cpp
        ProgGrafica_2024/MainClase/System.h
        ProgGrafica_2024/MainClase/Colliders.cpp
        ProgGrafica_2024/MainClase/Colliders.h
)
target_include_directories(MainClase PRIVATE ${CMAKE_SOURCE_DIR}/ProgGrafica_2024/MainClase)
target_link_libraries(MainClase glfw3 opengl32)

add_custom_command(TARGET MainClase POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/ProgGrafica_2024/MainClase/data
        $<TARGET_FILE_DIR:MainClase>/data
)

# ============================================================================
# PROYECTOS ADICIONALES (generados por nuevo_proyecto.bat)
# ============================================================================


# NUEVO_PROYECTO_AQUI
