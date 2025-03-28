#!/bin/bash

# Configuración de rutas
SRC_FILE="../EmployeeDataParser.cpp"
OUT_FILE="EmployeeDataParser"
VCPKG_DIR="/c/dev/c++/vcpkg/installed/x64-windows"

# Verificar si el archivo fuente existe
if [ ! -f "$SRC_FILE" ]; then
    echo "❌ Error: No se encontró el archivo fuente $SRC_FILE"
    read -p "Presiona Enter para salir..."
    exit 1
fi

# Verificar si la biblioteca pugixml.lib existe (no es necesario en este caso si están los archivos .cpp y .hpp)
if [ ! -f "../pugixml.cpp" ] || [ ! -f "../pugixml.hpp" ]; then
    echo "❌ Error: No se encontró los archivos pugixml.cpp o pugixml.hpp en el directorio."
    read -p "Presiona Enter para salir..."
    exit 1
fi

# Compilación con rutas explícitas para nlohmann JSON y pugixml
g++ "$SRC_FILE" ../pugixml.cpp -o "$OUT_FILE" \
    -I"${VCPKG_DIR}/include/nlohmann" 

# Verificar si la compilación fue exitosa
if [ $? -ne 0 ]; then
    echo "❌ Error: Falló la compilación."
    read -p "Presiona Enter para salir..."
    exit 1
fi

echo "✅ Compilación exitosa. Ejecutando el programa..."

# Archivos de prueba
XML_FILE="../data/employees_1.xml"
JSON_FILE="../data/employees_1.json"

# Verificar que los archivos de prueba existen
if [ ! -f "$XML_FILE" ]; then
    echo "⚠️ Advertencia: No se encontró $XML_FILE"
fi

if [ ! -f "$JSON_FILE" ]; then
    echo "⚠️ Advertencia: No se encontró $JSON_FILE"
fi

# Ejecutar el programa
./"$OUT_FILE" "$XML_FILE" "$JSON_FILE"

# Evitar que la ventana se cierre de inmediato
read -p "Presiona Enter para salir..."