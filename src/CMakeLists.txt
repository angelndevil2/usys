cmake_minimum_required( VERSION 3.0 )

project ( "usys" VERSION 0.0.1 )

set ( CMAKE_VERBOSE_MAKEFILE true )

set ( OUTPUT_ELF
        "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION}"
        )
set ( SRC_FILES
        main.cc
        )

set ( CMAKE_C_COMPILER "gcc" )
set ( CMAKE_CXX_COMPILER "g++" )

# c++11 for stol
add_compile_options(-g -Wall -std=c++11)
set ( CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -pthread" )

# LINK_LIBRARIES(  )
# LINK_DIRECTORIES ( /usr/lib )

set ( CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS" )
set ( CMAKE_EXE_LINKER_FLAGS_DEBUG "-DDEBUG -DLINKER_FLAGS" )

set ( CMAKE_C_FLAGS_RELEASE "-DRELEASE -DC_FLAGS" )
set ( CMAKE_EXE_LINKER_FLAGS_RELEASE "-DRELEASE -DLINKER_FLAGS -s" )
set (CMAKE_SHARED_LINKER_FLAGS "-DLINKER_FLAGS -s")

## library make
set (LIB_NAME "${CMAKE_PROJECT_NAME}")
add_library( ${LIB_NAME} SHARED
    kernel_conf.cc
    proc_stat.cc
    proc_stat_thread.cc
    thread/thread_control.cc
    thread/usys_thread.cc
    )

add_executable(${OUTPUT_ELF} ${SRC_FILES})
target_link_libraries(${OUTPUT_ELF} ${LIB_NAME})

