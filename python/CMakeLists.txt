cmake_minimum_required( VERSION 3.0 )

find_program(PYTHON "python")

if (PYTHON)

project ( "usys" VERSION 0.0.1 )

#set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
#set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
#set(DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/python/__init__.py")
set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build")

add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${PYTHON}
                       ARGS setup.py build)

add_custom_target(py-wrapper ALL DEPENDS ${OUTPUT})

endif()