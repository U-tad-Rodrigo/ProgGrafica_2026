@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo ╔════════════════════════════════════════════════════════════╗
echo ║       CREAR NUEVO PROYECTO - ProgGrafica_2024              ║
echo ╚════════════════════════════════════════════════════════════╝
echo.

set /p NOMBRE="Introduce el nombre del nuevo proyecto: "

if "%NOMBRE%"=="" (
    echo [ERROR] El nombre no puede estar vacio.
    pause
    exit /b 1
)

:: Verificar si ya existe
if exist "ProgGrafica_2024\%NOMBRE%" (
    echo [ERROR] El proyecto "%NOMBRE%" ya existe.
    pause
    exit /b 1
)

echo.
echo [1/4] Creando carpeta del proyecto...
mkdir "ProgGrafica_2024\%NOMBRE%"

echo [2/4] Copiando archivos Common al proyecto...
copy "ProgGrafica_2024\Common\*.h" "ProgGrafica_2024\%NOMBRE%\" >nul
copy "ProgGrafica_2024\Common\*.cpp" "ProgGrafica_2024\%NOMBRE%\" >nul

echo [3/4] Creando main.cpp con plantilla basica...
(
echo #define GLAD_BIN
echo #include "common.h"
echo #include "EventManager.h"
echo.
echo int main^(int argc, char** argv^)
echo {
echo     return 0;
echo }
) > "ProgGrafica_2024\%NOMBRE%\main.cpp"

echo [4/4] Actualizando CMakeLists.txt...

powershell -Command "$cmake = \"`n# --- Proyecto: %NOMBRE% ---`nadd_executable(%NOMBRE%`n    ProgGrafica_2024/%NOMBRE%/main.cpp`n    ProgGrafica_2024/%NOMBRE%/common.h`n    ProgGrafica_2024/%NOMBRE%/EventManager.cpp`n    ProgGrafica_2024/%NOMBRE%/EventManager.h`n    ProgGrafica_2024/%NOMBRE%/Object3D.cpp`n    ProgGrafica_2024/%NOMBRE%/Object3D.h`n    ProgGrafica_2024/%NOMBRE%/libMath.cpp`n    ProgGrafica_2024/%NOMBRE%/libMath.h`n)`ntarget_include_directories(%NOMBRE% PRIVATE `${CMAKE_SOURCE_DIR}/ProgGrafica_2024/%NOMBRE%)`ntarget_link_libraries(%NOMBRE% glfw3 opengl32)`n`n# NUEVO_PROYECTO_AQUI\"; (Get-Content 'CMakeLists.txt' -Raw) -replace '# NUEVO_PROYECTO_AQUI', $cmake | Set-Content 'CMakeLists.txt' -NoNewline"

echo.
echo ════════════════════════════════════════════════════════════
echo   Proyecto "%NOMBRE%" creado!
echo   Carpeta: ProgGrafica_2024\%NOMBRE%\
echo   Recarga CMake en tu IDE.
echo ════════════════════════════════════════════════════════════
pause

