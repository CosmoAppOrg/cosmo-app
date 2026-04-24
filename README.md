# Cosmo App

A "batteries-included" template for building cross-platform C++ console applications using **Cosmopolitan Libc** that are fully self-contained (statically linked). It serves dual purposes: (1) a working reference application demonstrating 16 third-party C++ libraries, and (2) a reusable project template that engineers can clone and rename to bootstrap new C++ tools.

The core design philosophy is **maximum binary self-containment**: end-users download a single archive, extract it, and run the executable with no redistributables, runtime installers, or package managers required.

## What is Cosmopolitan Libc?

Cosmopolitan Libc makes C a build-once-run-anywhere language. The resulting binary is a "fat ELF" that runs on Linux, macOS, Windows, FreeBSD, OpenBSD, NetBSD, and even in the BIOS boot environment.

## Features

- **Single binary**: No dependencies, no installation. Just copy and run.
- **16 library demonstrations**: See `src/main.cpp` for examples of:
  - CLI11 (command-line parsing)
  - nlohmann/json (JSON parsing)
  - Asio (asynchronous I/O)
  - cpp-httplib (HTTP client)
  - std::filesystem (directory enumeration)
  - std::regex (pattern matching)
  - std::thread / std::future (multithreading)
  - C++17 algorithms (transform, copy_if, reduce)
  - Embedded resource access (linker-baked JSON)
  - spdlog (fast, structured logging)
  - ada-url (WHATWG URL parsing)
  - stduuid (UUID generation)
  - reproc (child process execution)
  - cpptrace (stack tracing)
  - Howard Hinnant's Date (calendar arithmetic)
  - Vince's CSV Parser (CSV parsing)
- **Production logic example**: See `src/math_utils.*` for a simple, tested library.
- **Embedded resource**: `data/sample.json` is baked into the binary at compile time.
- **Cross-platform build**: Uses CMake with a Cosmopolitan toolchain.
- **Testing**: Google Test unit tests for production logic.

## Prerequisites

- [Cosmopolitan SDK](https://justine.lol/cosmopolitan/) (or just the cosmocc compiler)
- CMake 3.20+
- A C++17 compiler (Cosmopolitan's clang wrapper is used)

## Building

```bash
# Clone the repository
git clone https://github.com/yourname/cosmo-app.git
cd cosmo-app

# Configure and build
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cosmopolitan.cmake
cmake --build .
```

The resulting executable `cosmoapp` (or `cosmoapp.exe` on Windows) will be in the `build/` directory.

## Running

```bash
./cosmoapp --help
./cosmoapp --host api.example.com --port 8080
```

## Project Structure

```
cosmo-app/
├── .github/                # CI/CD workflows
├── data/                   # Embedded resources (sample.json)
├── docs/                   # Architecture, constraints, and workflow guides
├── scripts/                # Verification scripts
├── src/                    # Source code
│   ├── main.cpp            # Entry point + library demonstrations
│   ├── math_utils.cpp      # Production logic (add function)
│   ├── math_utils.h        # Header for math_utils
│   ├── embedded_resource.cpp # Access to embedded JSON
│   ├── embedded_resource.h   # Header for embedded_resource
│   └── logger.h            # spdlog setup utility
├── tests/                  # Unit tests
│   ├── CMakeLists.txt
│   └── test_math_utils.cpp
├── CMakeLists.txt          # Top-level CMake configuration
├── vcpkg.json              # Dependency manifest (built with cosmocc)
├── cosmopolitan.cmake      # Cosmopolitan toolchain file
├── README.md               # This file
├── AGENTS.md               # AI agent guidelines
└── CLAUDE.md               # Redirects to AGENTS.md
```

## Updating the Template

See [docs/TEMPLATE_WORKFLOW.md](docs/TEMPLATE_WORKFLOW.md) for instructions on cloning this template to create a new tool.

## License

MIT License - see the LICENSE file for details.

## Acknowledgments

This project is inspired by the [cpp-app](https://github.com/yourname/cpp-app) template but targets Cosmopolitan Libc for maximal portability.