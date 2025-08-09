cmake_minimum_required(VERSION 3.10)
project(guiarstr VERSION 1.3.0 DESCRIPTION "An advanced string manipulation library for C")

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Include directories
include_directories(include)

# Source files
set(LIB_SOURCES src/guiarstr.c)

# Library
add_library(guiarstr STATIC ${LIB_SOURCES})
add_library(guiarstr::guiarstr ALIAS guiarstr)

# Shared library
add_library(guiarstr_shared SHARED ${LIB_SOURCES})
set_target_properties(guiarstr_shared PROPERTIES OUTPUT_NAME guiarstr)
add_library(guiarstr::guiarstr_shared ALIAS guiarstr)

# Install
include(GNUInstallDirs)

install(TARGETS guiarstr guiarstr_shared
        EXPORT guiarstrTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES include/guiarstr.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# pkg-config
configure_file(guiarstr.pc.in guiarstr.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/guiarstr.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# CMake config
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/guiarstrConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(EXPORT guiarstrTargets
        FILE guiarstrTargets.cmake
        NAMESPACE guiarstr::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/guiarstr)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/guiarstrConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/guiarstr)

# Tests
enable_testing()
add_executable(guiarstr_tests tests/main.c)
target_link_libraries(guiarstr_tests guiarstr)
# Link with math library if available
if(UNIX AND NOT APPLE)
    find_library(M_LIBRARY m)
    if(M_LIBRARY)
        target_link_libraries(guiarstr_tests ${M_LIBRARY})
    endif()
endif()
add_test(NAME guiarstr_tests COMMAND guiarstr_tests)

# Example
add_executable(usage examples/usage.c)
target_link_libraries(usage guiarstr)
