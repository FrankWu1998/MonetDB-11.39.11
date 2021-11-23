# Install script for directory: /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/gdk/monetdb-gdk.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmonetdbx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so.21.1.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so.21"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/usr/local/lib:/usr/local/lib/monetdb5")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/gdk/libbat.so.21.1.1"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/gdk/libbat.so.21"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so.21.1.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so.21"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/common/stream:"
           NEW_RPATH "/usr/local/lib:/usr/local/lib/monetdb5")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmonetdbdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so"
         RPATH "/usr/local/lib:/usr/local/lib/monetdb5")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/gdk/libbat.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so"
         OLD_RPATH "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/common/stream:"
         NEW_RPATH "/usr/local/lib:/usr/local/lib/monetdb5")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbat.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmonetdbdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/monetdb" TYPE FILE FILES
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk.h"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk_system.h"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk_posix.h"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk_atoms.h"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk_tracer.h"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk_delta.h"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk_hash.h"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk_bbp.h"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk_utils.h"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk_cand.h"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/gdk/gdk_calc.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmonetdbdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/gdkTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/gdkTargets.cmake"
         "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/gdk/CMakeFiles/Export/share/monetdb/cmake/gdkTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/gdkTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/gdkTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/gdk/CMakeFiles/Export/share/monetdb/cmake/gdkTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/gdk/CMakeFiles/Export/share/monetdb/cmake/gdkTargets-noconfig.cmake")
  endif()
endif()

