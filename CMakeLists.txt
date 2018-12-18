#
# This file is part of the E_Geometry library.
# Copyright (C) 2009-2013 Benjamin Eikel <benjamin@eikel.org>
#
# This library is subject to the terms of the Mozilla Public License, v. 2.0.
# You should have received a copy of the MPL along with this library; see the 
# file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.1.0)
project(E_Geometry VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set up install directories
include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKECONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/E_Geometry)

add_library(E_Geometry
	E_Box.cpp
	ELibGeometry.cpp
	E_Frustum.cpp
	E_Line3.cpp
	E_Matrix3x3.cpp
	E_Matrix4x4.cpp
	E_Plane.cpp
	E_PointOctree.cpp
	E_Quaternion.cpp
	E_Ray3.cpp
	E_Rect.cpp
	E_Segment3.cpp
	E_Sphere.cpp
	E_SRT.cpp
	E_Tetrahedron.cpp
	E_Triangle.cpp
	E_Vec2.cpp
	E_Vec3.cpp
	E_Vec4.cpp
)

# Dependency to EScript
if(NOT TARGET EScript)
	find_package(EScript 0.6.7 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_Geometry LINK_PUBLIC EScript)

# Dependency to Geometry
if(NOT TARGET Geometry)
	find_package(Geometry 0.2.0 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_Geometry LINK_PUBLIC Geometry)

# Set version of library
set_target_properties(E_Geometry PROPERTIES VERSION ${E_Geometry_VERSION}
                                            SOVERSION ${E_Geometry_VERSION_MAJOR})

# Install the header files
file(GLOB E_GEOMETRY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${E_GEOMETRY_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_Geometry COMPONENT headers)

# Install the library
install(TARGETS E_Geometry EXPORT LibraryExport
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtimelibraries
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtimelibraries
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT developmentlibraries
)

# Set include directories for users of this library
target_include_directories(E_Geometry
                           INTERFACE
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
                           "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

# Library export
install(EXPORT LibraryExport DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR} FILE E_GeometryTargets.cmake COMPONENT developmentlibraries)

# Create the configuration files
include(CMakePackageConfigHelpers)
configure_package_config_file(E_GeometryConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/E_GeometryConfig.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR}
                              PATH_VARS CMAKE_INSTALL_CMAKECONFIGDIR
                              NO_SET_AND_CHECK_MACRO
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/E_GeometryConfigVersion.cmake
                                 VERSION ${E_Geometry_VERSION}
                                 COMPATIBILITY SameMajorVersion)

# Install the configuration files
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/E_GeometryConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/E_GeometryConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR} COMPONENT developmentlibraries)

# Packaging
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "libgeometry${E_Geometry_VERSION_MAJOR}-escript")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "E_Geometry library")
set(CPACK_PACKAGE_VENDOR "Benjamin Eikel; Claudius Jaehn; Ralf Petring")
set(CPACK_PACKAGE_CONTACT "Benjamin Eikel <benjamin@eikel.org>")
set(CPACK_PACKAGE_VERSION_MAJOR ${E_Geometry_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${E_Geometry_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${E_Geometry_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME "libE_Geometry")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_STRIP_FILES ON)

include(CPack)
