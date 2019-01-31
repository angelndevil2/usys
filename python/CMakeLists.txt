cmake_minimum_required( VERSION 2.8 )

find_program(PYTHON "python")

if (PYTHON)

project("usys")
set ( PROJECT_VERSION_MAJOR 0 )
set ( PROJECT_VERSION_MINOR 1 )

#set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
#set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
#set(DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/python/__init__.py")
set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build")

add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${PYTHON}
                       ARGS setup.py build)

add_custom_target(target ALL DEPENDS ${OUTPUT})

endif()