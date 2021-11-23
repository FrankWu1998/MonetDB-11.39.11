# Install script for directory: /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/merovingian/daemon/config

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/logrotate.d" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/merovingian/daemon/config/monetdbd")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsqlx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/systemd/system" TYPE FILE FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/merovingian/daemon/config/monetdbd.service")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsqlx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/var/monetdb5/dbfarm" TYPE FILE FILES
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/merovingian/daemon/config/.merovingian_properties"
    "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/merovingian/daemon/config/.merovingian_lock"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsqlx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/var/log/monetdb" TYPE DIRECTORY FILES "")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsqlx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/var/run/monetdb" TYPE DIRECTORY FILES "")
endif()

