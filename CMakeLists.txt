cmake_minimum_required(VERSION 3.20)
project(cosmoapp LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include vcpkg if available
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cosmopolitan.cmake" CACHE STRING "Cosmopolitan toolchain for vcpkg")
  include("${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# Static library for production logic
add_library(${PROJECT_NAME}_lib STATIC
  src/math_utils.cpp
  src/embedded_resource.cpp
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>
)

# Find packages via vcpkg (if used) or find_package
# We'll try to find the libraries via vcpkg's imported targets.
# If vcpkg is not used, we rely on find_package or manual inclusion.
# For simplicity, we assume vcpkg is used and provides the following packages:
#   CLI11, nlohmann-json, asio, cpp-httplib, spdlog, ada-url, stduuid, reproc, cpptrace, date, csv
# Note: Some package names might differ.

# We'll attempt to find each package. If not found, we'll print a warning but continue.
# The demo in main.cpp uses #ifdef to skip sections if a library is not found.

# CLI11
find_package(CLI11 QUIET)
if(CLI11_FOUND)
  target_include_directories(${PROJECT_NAME}_lib PRIVATE ${CLI11_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE CLI11::CLI11)
endif()

# nlohmann/json
find_package(nlohmann_json QUIET)
if(nlohmann_json_FOUND)
  target_include_directories(${PROJECT_NAME}_lib PRIVATE ${nlohmann_json_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE nlohmann_json::nlohmann_json)
endif()

# Asio (standalone)
find_package(asio QUIET)
if(asio_FOUND)
  target_include_directories(${PROJECT_NAME}_lib PRIVATE ${asio_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE asio::asio)
endif()

# cpp-httplib
find_package(httplib QUIET)
if(httplib_FOUND)
  target_include_directories(${PROJECT_NAME}_lib PRIVATE ${httplib_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE httplib::httplib)
endif()

# spdlog
find_package(spdlog QUIET)
if(spdlog_FOUND)
  target_include_directories(${PROJECT_NAME}_lib PRIVATE ${spdlog_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE spdlog::spdlog)
endif()

# ada-url
find_package(ada QUIET)
if(ada_FOUND)
  target_include_directories(${PROJECT_NAME}_lib PRIVATE ${ada_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE ada::ada)
endif()

# stduuid
find_package(stduuid QUIET)
if(stduuid_FOUND)
  target_include_directories(${PROJECT_NAME}_lib PRIVATE ${stduuid_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE stduuid::stduuid)
endif()

# reproc
find_package(reproc QUIET)
if(reproc_FOUND)
  target_include_directories(${PROJECT_NAME}_lib PRIVATE ${reproc_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE reproc::reproc)
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE reproc::reproc++)
endif()

# cpptrace
find_package(cpptrace QUIET)
IF(cpptrace_FOUND)
  target_include_directories(${PROJECT_NAME}_lib PRIVATE ${cpptrace_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE cpptrace::cpptrace)
ENDIF()

# date (Howard Hinnant's date)
find_package(date QUIET)
IF(date_FOUND)
  target_include_directories(${PROJECT_NAME}_lib PRIVATE ${date_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME}_lib PRIVATE date::date)
ENDIF()

# csv (Vince's CSV Parser)
# Note: There might not be a CMake package for this. We'll skip for now and rely on the user to have it in their include path.
# We can try to find it via FindCSV.cmake or just include the single header.
# For simplicity, we assume the user has the header in their include path or we provide it in extern.

# Executable target
add_executable(${PROJECT_NAME}
  src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE ${PROJECT_NAME}_lib
)

# Install rules (optional)
install(TARGETS ${PROJECT_NAME}_lib ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)