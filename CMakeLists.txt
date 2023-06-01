cmake_minimum_required(VERSION 3.12)
project(contact_book VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER g++)

# Add the include directories
include_directories(includes)

# Add the source files
set(SOURCES
    sources/book.cpp
    sources/main.cpp
    sources/backend.cpp
    sources/frontend.cpp
)

# Add the executable
add_executable(contact_book ${SOURCES})

# Platform-specific configurations
if(WIN32)
    # Windows-specific configuration
    # Add any Windows-specific libraries or flags here
elseif(UNIX AND NOT APPLE)
    # Linux-specific configuration
    # Add any Linux-specific libraries or flags here
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

# Find and include SFML
find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Link SFML libraries
target_link_libraries(contact_book sfml-graphics sfml-window)