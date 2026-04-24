# Architecture

## Overview

Cosmo App is a "batteries-included" template for building cross-platform C++ console applications using **Cosmopolitan Libc**. The goal is to produce a single, static, portable executable that runs on Linux, macOS, Windows, FreeBSD, and more without any dependencies.

## Key Design Decisions

### 1. **Cosmopolitan Libc Only**

- The entire project is built with the Cosmopolitan Libc toolchain (`cosmocc`).
- This results in a "fat ELF" binary that is truly portable across multiple operating systems.
- No platform-specific code or conditional compilation is needed for the core functionality.

### 2. **Static Linking**

- All dependencies are statically linked into the executable.
- The binary is self-contained: no external DLLs, .so files, or dylibs are required.
- This is achieved by using the `-static` and `-nostdlib` flags with the Cosmopolitan compiler.

### 3. **Modular Structure**

- **Production Logic**: Separated into a static library (`cosmoapp_lib`) containing `math_utils`, `embedded_resource`, and `logger`.
- **Executable**: A thin executable target (`cosmoapp`) that contains only `main.cpp` and links against the production library.
- This separation allows the production logic to be tested and reused independently.

### 4. **Library Demonstrations**

- The `main.cpp` file demonstrates 16 popular C++ libraries.
- Each demonstration is conditionally compiled based on whether the library was found during configuration.
- If a library is not found, the demo is skipped and a message is printed.

### 5. **Embedded Resources**

- The `data/sample.json` file is embedded into the binary at link time using `llvm-objcopy`.
- The `embedded_resource` module provides a `string_view` to the embedded data, avoiding runtime file I/O.

### 6. **Logging**

- Uses `spdlog` with two sinks: colored console output and a rotating file log.
- The logger is set up in a header-only utility for easy reuse.

### 7. **Testing**

- Google Test is used for unit testing the production logic.
- The test executable is also built with Cosmopolitan, making it portable.

## Build System

- **CMake**: Used as the primary build system.
- **Toolchain**: A custom CMake toolchain file (`cosmopolitan.cmake`) configures the compiler to use `cosmocc` and sets the necessary flags for static, portable binaries.
- **Dependency Management**: Uses `vcpkg` in manifest mode to fetch and build dependencies as static libraries with the Cosmopolitan toolchain.

## Portability

The resulting binary from the Cosmopolitan toolchain runs on:
- Linux (x86_64, aarch64)
- macOS (x86_64, arm64)
- Windows (x86_64)
- FreeBSD (x86_64)
- OpenBSD (x86_64)
- NetBSD (x86_64)
- And even in the BIOS boot environment (x86_64)

This is achieved without any recompilation for each target.