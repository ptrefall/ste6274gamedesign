
cmake_minimum_required(VERSION 2.8)

# set a default build type if none was provided
# this has to be done before the project() instruction!
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# project name
project(GameDesignClient)

# include the configuration file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

# setup version numbers
set(VERSION_MAJOR 2)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif(MSVC)

# add the header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/depends)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/depends/Factotum/src)

# add an option for choosing the build type (shared or static)
set(BUILD_SHARED_LIBS FALSE CACHE BOOL "TRUE to build project as shared libraries, FALSE to build it as static libraries")

# define SFML_STATIC if the build type is not set to 'shared'
if(NOT BUILD_SHARED_LIBS)
	add_definitions(-DGLEW_STATIC)
endif()

# remove SL security warnings with Visual C++
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif()

# define an option for choosing between static and dynamic C runtime (Windows only)
if(WINDOWS)
    set(STATIC_STD_LIBS TRUE CACHE BOOL "TRUE to statically link to the standard libraries, FALSE to use them as DLLs")
    
    # for VC++, we can apply it globally by modifying the compiler flags
    if(COMPILER_MSVC AND STATIC_STD_LIBS)
        foreach(flag
                CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
            endif()
        endforeach()
    endif()
endif()

# disable the rpath stuff
set(CMAKE_SKIP_BUILD_RPATH TRUE)

# add the subdirectories
add_subdirectory(src)
add_subdirectory(depends/Factotum/src)
# add_subdirectory(shaders)
