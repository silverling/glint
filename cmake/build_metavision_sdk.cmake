include(ExternalProject)


set(METAVISION_SDK_BUILD_DIR "${CMAKE_BINARY_DIR}/metavision_sdk/build")
set(METAVISION_SDK_INSTALL_DIR "${CMAKE_BINARY_DIR}/metavision_sdk/install")

ExternalProject_Add(
    metavision_sdk
    PREFIX ${CMAKE_BINARY_DIR}/metavision_sdk
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendors/openeb
    BINARY_DIR ${METAVISION_SDK_BUILD_DIR}
    INSTALL_DIR ${METAVISION_SDK_INSTALL_DIR}
    CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=Release
    -DCMAKE_INSTALL_PREFIX=${METAVISION_SDK_INSTALL_DIR}
    -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
    -DCMAKE_CXX_STANDARD=17
    -DCOMPILE_PYTHON3_BINDINGS=OFF
    -DBUILD_SAMPLES=OFF
    -DUDEV_RULES_SYSTEM_INSTALL=OFF
)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${METAVISION_SDK_INSTALL_DIR}" CACHE STRING "Directories to search for packages" FORCE)

# Create directories that will be needed by the imported targets
# This prevents CMake from failing during the configuration phase
file(MAKE_DIRECTORY "${METAVISION_SDK_INSTALL_DIR}/include")
file(MAKE_DIRECTORY "${METAVISION_SDK_INSTALL_DIR}/lib")

# Create imported targets for MetavisionSDK components
add_library(MetavisionSDK::core SHARED IMPORTED)
set_target_properties(MetavisionSDK::core PROPERTIES
    IMPORTED_LOCATION "${METAVISION_SDK_INSTALL_DIR}/lib/libmetavision_sdk_core.so"
    INTERFACE_INCLUDE_DIRECTORIES "${METAVISION_SDK_INSTALL_DIR}/include"
)
add_dependencies(MetavisionSDK::core metavision_sdk)

add_library(MetavisionSDK::stream SHARED IMPORTED)
set_target_properties(MetavisionSDK::stream PROPERTIES
    IMPORTED_LOCATION "${METAVISION_SDK_INSTALL_DIR}/lib/libmetavision_sdk_stream.so"
    INTERFACE_INCLUDE_DIRECTORIES "${METAVISION_SDK_INSTALL_DIR}/include"
)
add_dependencies(MetavisionSDK::stream metavision_sdk)
