Image Box Filter using NVIDIA NPP with CUDA

Overview
This project demonstrates the use of the NVIDIA Performance Primitives (NPP) library with CUDA to perform a box filter on images. The goal is to utilize GPU acceleration to efficiently smooth images by averaging neighboring pixels, leveraging the computational power of modern GPUs. The project is a part of the CUDA at Scale for the Enterprise course and serves as a template for understanding how to implement basic image processing operations using CUDA and NPP.

Code Organization
bin/ This folder should hold all binary/executable code that is built automatically or manually. Executable code should use the .exe extension on Windows or be compiled binaries on Linux.

data/ This folder should hold all example input and output images in supported formats such as PNG, PGM, or BMP.

lib/ Any third-party libraries not installed via the system package manager can be placed here for easy linking.

src/ The CUDA and C++ source code should be placed here in a structured way.

README.md This file contains the description of the project, including setup, build, and usage instructions.

INSTALL This file can hold detailed instructions for installing dependencies across different operating systems.

Makefile or CMakeLists.txt or build.sh Scripts for compiling the project in an automatic fashion.

run.sh Optional script to run the executable with or without command-line arguments.

Key Concepts
Performance Strategies, Image Processing, NPP Library

Supported SM Architectures
SM 3.5
SM 3.7
SM 5.0
SM 5.2
SM 6.0
SM 6.1
SM 7.0
SM 7.2
SM 7.5
SM 8.0
SM 8.6

Supported Operating Systems
Linux, Windows

Supported CPU Architectures
x86_64, ppc64le, armv7l

CUDA APIs involved
NPP image filtering APIs
CUDA memory management APIs

Dependencies needed to build and run
FreeImage library for image I/O
NPP library (part of CUDA Toolkit)

Prerequisites
Download and install the CUDA Toolkit (11.4 or later) for your platform. Ensure that FreeImage and NPP dependencies are installed.

Build and Run

Windows
On Windows, the project can be built using Visual Studio solution files (.sln). Each solution file corresponds to a supported version of Visual Studio. To build all samples, use the complete solution files. To build only one sample, use the project-level solution.

Note: Some samples may require the Microsoft DirectX SDK (June 2010 or newer). Ensure that the VC++ directories are properly set in Visual Studio (Tools > Options).

Linux
On Linux, the project can be built using makefiles. Navigate to the source directory and run:

make

Available build options include:
make TARGET_ARCH=x86_64
make TARGET_ARCH=ppc64le
make TARGET_ARCH=armv7l
make dbg=1 (to include debug symbols)
make SMS="50 60" (to target specific GPU architectures)
make HOST_COMPILER=g++ (to specify a host compiler)

Running the Program
After building, you can run the program with:

make run

This will execute the binary, applying a box filter to the input image (for example grey-sloth.png) and save the result as grey-sloth_boxFilter.png in the data or output directory.

Alternatively, you can run the binary directly:
./bin/boxFilterNPP --input data/grey-sloth.png --output data/grey-sloth_boxFilter.png

Cleaning Up
To remove compiled binaries and generated files, run:

make clean

This will delete everything inside the bin/ directory.
