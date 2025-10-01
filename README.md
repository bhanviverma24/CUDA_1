# Image Box Filter using NVIDIA NPP with CUDA

## Overview

This project demonstrates the use of the **NVIDIA Performance Primitives (NPP)** library with **CUDA** to perform a **box filter** on images.
The goal is to use **GPU acceleration** to efficiently smooth images by averaging neighboring pixels, leveraging the computational power of modern GPUs.

This project is part of the *CUDA at Scale for the Enterprise* course and serves as a template for implementing basic image processing operations using CUDA and NPP.

---

## Code Organization

* **bin/** – Contains compiled binaries or executables
* **data/** – Example input/output images (PNG, PGM, BMP, etc.)
* **lib/** – Third-party libraries not installed via the system package manager
* **src/** – Source code (CUDA + C++)
* **README.md** – Project description (this file)
* **INSTALL** – Instructions for installation and dependencies
* **Makefile / CMakeLists.txt / build.sh** – Build scripts
* **run.sh** – Optional script to run executables

---

## Key Concepts

* Performance Strategies
* Image Processing
* NPP Library

---

## Supported Architectures

* **GPU SM Architectures:** 3.5, 3.7, 5.0, 5.2, 6.0, 6.1, 7.0, 7.2, 7.5, 8.0, 8.6
* **Operating Systems:** Linux, Windows
* **CPU Architectures:** x86_64, ppc64le, armv7l

---

## CUDA APIs Used

* NPP image filtering APIs
* CUDA memory management APIs

---

## Dependencies

* **CUDA Toolkit (11.4 or later)**
* **NPP (bundled with CUDA Toolkit)**
* **FreeImage** (for image I/O)

---

## Prerequisites

1. Install CUDA Toolkit (11.4 or newer).
2. Ensure FreeImage and NPP dependencies are installed.
3. Verify GPU support for the target architecture.

---

## Build and Run

### On Linux

```bash
cd boxFilterNPP
make
make run
```

### On Windows

* Open the `.sln` file in **Visual Studio**.
* Build the solution.
* Run the executable.

---

## Running the Program

Default execution after build:

```bash
make run
```

This applies a **box filter** to the input image (for example `grey-sloth.png`) and saves the result as `grey-sloth_boxFilter.png`.

To run manually with custom input/output:

```bash
./bin/boxFilterNPP --input data/grey-sloth.png --output data/grey-sloth_boxFilter.png
```

---

## Cleaning Up

To remove binaries and temporary files:

```bash
make clean
```
