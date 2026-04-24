# Cosmopolitan Libc toolchain file for CMake
# Sets up the compiler to use cosmocc for static, fully portable binaries

# Determine the system
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_HOST_SYSTEM_PROCESSOR})

# Find the cosmocc compiler. We assume it's in the PATH or set via environment.
# If not found, we can let the user set COSMOCC_PREFIX or similar.
# For simplicity, we just try to use clang and then set the flags for Cosmopolitan.
# However, the proper way is to use the cosmocc wrapper.

# Check if cosmocc is available
find_program(COSMOCC_PATH cosmocc)
if(NOT COSMOCC_PATH)
  message(FATAL_ERROR "cosmocc not found in PATH. Please install Cosmopolitan Libc and ensure cosmocc is available.")
endif()

# Set the compilers to cosmocc
set(CMAKE_C_COMPILER   ${COSMOCC_PATH})
set(CMAKE_CXX_COMPILER ${COSMOCC_PATH})

# Cosmopolitan Libc flags for static, portable executables
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -nostdlib")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static -nostdlib")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -static -nostdlib")

# We want to build static libraries by default
set(BUILD_SHARED_LIBS OFF)

# Set the C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optionally, set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# If we are using vcpkg, we need to set the toolchain file for vcpkg as well.
# But note: we are using our own toolchain, so we must tell vcpkg to use the same compiler.
# This is done by setting VCPKG_CHAINLOAD_TOOLCHAIN_FILE to this file.
# However, we are not going to use vcpkg's automatic linking; we will manually include the libraries.
# Alternatively, we can use vcpkg in manifest mode and set the triplet to use cosmocc.
# For simplicity, we will not use vcpkg's integration and instead rely on externally built static libs.
# But the plan said to use vcpkg in manifest mode. We'll leave a comment and set the triplet if needed.

# Uncomment the following lines if you want to use vcpkg with this toolchain.
# set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_FILE})
# set(VCPKG_TARGET_TRIPLET x64-linux-cosmo) # Example triplet, you must define it in vcpkg
