# Constraints

## Technical Invariants

These constraints must never be violated. They define the boundaries of the system and guarantee its core properties.

### 1. **Binary Self-Containment**

- The final executable must be a single file that runs without any external dependencies (no DLLs, .so files, dylibs, or runtime installers).
- Achieved by static linking with Cosmopolitan Libc and the `-static -nostdlib` flags.

### 2. **Cosmopolitan Libc Only**

- The project must be built exclusively with the Cosmopolitan Libc toolchain (`cosmocc`).
- No platform-specific compilers (e.g., `clang-cl` for Windows, `clang` for Linux/macOS) are used.
- The resulting binary is a "fat ELF" that runs on Linux, macOS, Windows, FreeBSD, OpenBSD, NetBSD, and in the BIOS boot environment.

### 3. **C++17 Language Standard**

- All code must conform to the C++17 standard.
- No reliance on compiler-specific extensions or features from later standards (unless conditionally available and gracefully degraded).

### 4. **Production Logic Separation**

- Production logic (e.g., `math_utils`, `embedded_resource`, `logger`) must reside in a static library separate from the executable's entry point (`main.cpp`).
- This allows unit testing and reuse of the logic without pulling in the demonstration code.

### 5. **No Runtime File System Access for Embedded Resources**

- Embedded data (e.g., `data/sample.json`) must be accessed via a `string_view` pointing to memory embedded in the binary at link time.
- No runtime file I/O is permitted for these resources.

### 6. **Logging via spdlog with Dual Sinks**

- Logging must use `spdlog` with exactly two sinks:
  1. A colored console sink (stdout)
  2. A rotating file sink (5 MB max size, 3 files max)
- The logger must be named `"app"` and configured via the `logger.h` utility.

### 7. **Unit Testing with Google Test**

- Production logic must be covered by unit tests using Google Test.
- Test executables must also be built with the Cosmopolitan toolchain and be portable.

### 8. **Dependency Management via vcpkg (Manifest Mode)**

- Third-party dependencies must be declared in `vcpkg.json` and built as static libraries using the Cosmopolitan toolchain.
- The `vcpkg` toolchain file must be chained to the Cosmopolitan CMake toolchain.

### 9. **Cross-Platform Source Code**

- Source code must avoid platform-specific APIs where possible.
- When platform-specific code is unavoidable (e.g., in demonstrations), it must be conditionally compiled and gracefully degraded if the platform or library is not available.

## Rationale

These constraints ensure that Cosmo App remains a truly portable, self-contained template that can be used to build tools that run anywhere without installation or configuration.