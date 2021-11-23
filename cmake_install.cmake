# Install script for directory: /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmonetdbdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/monetdb_config_headerTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/monetdb_config_headerTargets.cmake"
         "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CMakeFiles/Export/share/monetdb/cmake/monetdb_config_headerTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/monetdb_config_headerTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/monetdb_config_headerTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CMakeFiles/Export/share/monetdb/cmake/monetdb_config_headerTargets.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmonetdbdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/monetdb" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/monetdb_config.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmonetdbdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/MonetDBConfig.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/common/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/clients/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/gdk/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/misc/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/monetdb5/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/geom/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/testing/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/buildtools/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/ctest/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/documentation/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
