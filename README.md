# Employee Data Parser - Windows Setup Guide

## Overview
This project is a command-line utility for parsing employee data from XML and JSON files. It supports calculations and sorting and includes unit tests using GoogleTest.

## Prerequisites
To build and run this project on Windows, you need the following tools:
- **g++ (MinGW-w64 or MSYS2)**
- **vcpkg (for package management)**
- **GoogleTest (for unit testing)**
- **pugixml (for XML parsing)**
- **nlohmann/json (for JSON parsing)**

---

## Installing Required Dependencies

### 1. Install `g++`
If you don’t have `g++` installed, install it via MSYS2:
```sh
pacman -S mingw-w64-x86_64-gcc
```
Or install MinGW-w64 separately from [Mingw-w64 official site](https://www.mingw-w64.org/).

### 2. Install `vcpkg`
Vcpkg is used for managing dependencies like `nlohmann/json`.

```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
```
After installation, integrate it with your system:
```sh
./vcpkg integrate install
```

### 3. Install `nlohmann/json` via vcpkg
```sh
./vcpkg install nlohmann-json:x64-windows
```

### 4. Setting up `pugixml`
Instead of using vcpkg, place the following files manually in your project root where `EmployeeDataParser.cpp` and `test_employee_parser.cpp` are located:
- `pugixml.cpp`
- `pugixml.hpp`
- `pugiconfig.hpp`

No additional installation is required.

### 5. Setting up GoogleTest
GoogleTest is included in the `gtest` folder within the project. Before running tests, compile GoogleTest:

```sh
g++ -c gtest/src/gtest-all.cc -I gtest/include
g++ -c gtest/src/gtest_main.cc -I gtest/include
ar rcs libgtest.a gtest-all.o gtest_main.o
```

This generates `libgtest.a`, required for linking during test compilation.

---

## Build and Run Instructions

### 1. Compile and Run the Main Program
Use `run.sh` to compile and execute the program with specific XML and JSON files:
```sh
./run.sh employees.xml employees.json
```

### 2. Compile and Run Unit Tests
Use `run_tests_1.sh` to compile and execute unit tests:
```sh
./run_tests_1.sh
```

This script will build the test suite and run all test cases.

---

## Additional Notes
- Ensure `g++` is installed and accessible in your system’s PATH.
- If `vcpkg` is not in your PATH, specify the full path when installing packages.
- If compilation fails due to missing headers, verify that `-I"path/to/include"` is correctly set in compilation scripts.

This guide should help you build, test, and run the Employee Data Parser project successfully on Windows. Happy coding!

