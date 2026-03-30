# AntiPirateScreen - C Library CMake Configuration
# Version: 2.0.0
# Author: TIBI624
# Branch: tibi624

cmake_minimum_required(VERSION 3.15)
project(AntiPirateScreen_C VERSION 2.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Author information
set(APS_AUTHOR "TIBI624")
set(APS_BRANCH "tibi624")

# Source files
set(SOURCES
    protection.c
)

set(HEADERS
    protection.h
)

# Create static library
add_library(antipiratescreen_c_static STATIC ${SOURCES} ${HEADERS})
set_target_properties(antipiratescreen_c_static PROPERTIES
    OUTPUT_NAME "AntiPirateScreen_c"
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER "${HEADERS}"
)

# Create shared library
add_library(antipiratescreen_c_shared SHARED ${SOURCES} ${HEADERS})
set_target_properties(antipiratescreen_c_shared PROPERTIES
    OUTPUT_NAME "AntiPirateScreen_c"
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER "${HEADERS}"
)

# Platform-specific settings
if(WIN32)
    target_link_libraries(antipiratescreen_c_shared PRIVATE user32)
endif()

# Installation
install(TARGETS antipiratescreen_c_static antipiratescreen_c_shared
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)