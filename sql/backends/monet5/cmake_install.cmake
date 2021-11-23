# Install script for directory: /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/sql/backends/monet5

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsqlx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so.11.39.11"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so.11"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/usr/local/lib:/usr/local/lib/monetdb5")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/backends/monet5/libmonetdbsql.so.11.39.11"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/backends/monet5/libmonetdbsql.so.11"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so.11.39.11"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so.11"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/monetdb5/tools:/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/gdk:/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/common/stream:"
           NEW_RPATH "/usr/local/lib:/usr/local/lib/monetdb5")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmonetdbdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so"
         RPATH "/usr/local/lib:/usr/local/lib/monetdb5")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/backends/monet5/libmonetdbsql.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so"
         OLD_RPATH "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/monetdb5/tools:/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/gdk:/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/common/stream:"
         NEW_RPATH "/usr/local/lib:/usr/local/lib/monetdb5")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmonetdbsql.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsqlx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/monetdb" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/sql/backends/monet5/sql_import.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmonetdbdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/sqlTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/sqlTargets.cmake"
         "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/backends/monet5/CMakeFiles/Export/share/monetdb/cmake/sqlTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/sqlTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake/sqlTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/backends/monet5/CMakeFiles/Export/share/monetdb/cmake/sqlTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/monetdb/cmake" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/backends/monet5/CMakeFiles/Export/share/monetdb/cmake/sqlTargets-noconfig.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/backends/monet5/generator/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/backends/monet5/UDF/cmake_install.cmake")
  include("/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/backends/monet5/vaults/cmake_install.cmake")

endif()

