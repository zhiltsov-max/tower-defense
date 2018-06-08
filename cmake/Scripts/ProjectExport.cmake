# Script to generage configuration files of the project.
# These files contain information about targets, package version and variables.
#
# Required variables:
#  - VERSION
#  - PROJECT_NAME
#
# Required files:
#  - <project>/cmake/${PROJECT_NAME}Config.cmake.in
#
# Target export requirements:
#  - ${PROJECT_NAME}Targets - should be used when installing target
#
# Outputs:
#  - <projectname>ConfigVersion.cmake
#  - <projectname>Config.cmake
#  - <projectname>Targets.cmake
# They are installed in lib/cmake/<projectname>.
# The project targets are installed under the ${PROJECT_NAME}:: namespace.
#

include(CMakePackageConfigHelpers)

# Destination for config files
set(CONFIG_INSTALL_DIR lib/cmake/${PROJECT_NAME})

# Add exported targets
export(EXPORT ${PROJECT_NAME}Targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
)

# Create config file
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
)

# Create version file
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${YART_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Targets installation
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CONFIG_INSTALL_DIR}
)

# Config files installation
install(FILES
        ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake
        ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CONFIG_INSTALL_DIR})