cmake_minimum_required( VERSION 2.8 )

project( "usys" )
set ( PROJECT_VERSION_MAJOR 0 )
set ( PROJECT_VERSION_MINOR 1 )

set ( CMAKE_VERBOSE_MAKEFILE true )

set ( OUTPUT_ELF
        "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
        )
set ( SRC_FILES
        main.cc
        )

set ( CMAKE_C_COMPILER "gcc" )
set ( CMAKE_CXX_COMPILER "g++" )

# c++11 for stol
add_compile_options(-g -Wall -std=c++11)
set ( CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections" )

# LINK_LIBRARIES(  )
# LINK_DIRECTORIES ( /usr/lib )

set ( CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS" )
set ( CMAKE_EXE_LINKER_FLAGS_DEBUG "-DDEBUG -DLINKER_FLAGS" )

set ( CMAKE_C_FLAGS_RELEASE "-DRELEASE -DC_FLAGS" )
set ( CMAKE_EXE_LINKER_FLAGS_RELEASE "-DRELEASE -DLINKER_FLAGS" )

## library make
set (LIB_NAME "usys")
add_library( ${LIB_NAME} SHARED
    kernel_conf.cc
    proc_stat.cc
    )

add_executable(${OUTPUT_ELF} ${SRC_FILES})
target_link_libraries(${OUTPUT_ELF} ${LIB_NAME})

