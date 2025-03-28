#!/bin/bash

# Configuración de rutas
TEST_SRC_FILE="../TestEmployeeParser.cpp"
SRC_FILE="../EmployeeDataParser.cpp"
OUT_FILE="test_runner"
VCPKG_DIR="/c/dev/c++/vcpkg/installed/x64-windows"

# Verificar si los archivos fuente existen
if [ ! -f "$TEST_SRC_FILE" ] || [ ! -f "$SRC_FILE" ]; then
    echo "Error: No se encontraron los archivos de código fuente necesarios."
    read -p "Presiona Enter para salir..."
    exit 1
fi

# Verificar si pugixml y nlohmann existen
if [ ! -f "../pugixml.cpp" ] || [ ! -f "../pugixml.hpp" ]; then
    echo "Error: No se encontraron los archivos pugixml.cpp o pugixml.hpp."
    read -p "Presiona Enter para salir..."
    exit 1
fi

# Compilación con Google Test y dependencias
g++ "$TEST_SRC_FILE" "$SRC_FILE" ../pugixml.cpp ../libgtest.a \
    -I"../gtest/include" \
    -I"${VCPKG_DIR}/include/nlohmann" \
    -lpthread -DTEST_BUILD -o "$OUT_FILE"

# Verificar si la compilación fue exitosa
if [ $? -ne 0 ]; then
    echo "Error: Falló la compilación."
    read -p "Presiona Enter para salir..."
    exit 1
fi

echo "Compilación exitosa. Ejecutando pruebas..."

# Ejecutar pruebas
./"$OUT_FILE"

# Evitar cierre inmediato de la terminal
read -p "Presiona Enter para salir..."
