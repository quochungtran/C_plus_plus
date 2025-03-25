The repo aims to self-learn C++20 

### Prerequisites

Before you begin, make sure you have the following tools installed on your Linux system:

- **CMake**: CMake is a cross-platform software used to manage the build process of source code. It enables the generation of native compilation rules under both Linux and Windows using common build scripts.

### Build Process

To compile the project, follow these steps:

1. Run the `bootstrap.sh` script:

   ```bash
   ./bootstrap.sh
   ```

This script configures the build process and generates a temporary build directory. Navigate to the build directory:

  ```bash
  cd build
  ```

Build process using CMake:

   ```bash
   make install
  ```

Running the executable outputs
  ```bash
   cd bin
   ./<name_of_binary>
  ```

The CMakeLists.txt file in the build directory contains the main CMake script, including lead compilation rules for the project.

### Project Structure
The project has the following directory structure:

* build: Directory to compile the code source using makefile
* src: All source code must be hosted in this directory.
* bin: Collections of compiled executable files


Feel free to explore the project, and contribute more algorithms in C++.