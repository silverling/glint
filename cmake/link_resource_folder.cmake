# Link `res` folder to `build/res` before build.

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(RESOURCE_DIR_BUILD "${CMAKE_BINARY_DIR}/res")

add_custom_command(
    OUTPUT ${RESOURCE_DIR_BUILD}
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${RESOURCE_DIR} ${RESOURCE_DIR_BUILD}
    DEPENDS ${RESOURCE_DIR}
    COMMENT "Creating symbolic link from ${RESOURCE_DIR} to ${RESOURCE_DIR_BUILD}"
)
add_custom_target(resource DEPENDS ${RESOURCE_DIR_BUILD})
