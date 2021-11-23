#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MonetDB::stream" for configuration ""
set_property(TARGET MonetDB::stream APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MonetDB::stream PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libstream.so.14.0.4"
  IMPORTED_SONAME_NOCONFIG "libstream.so.14"
  )

list(APPEND _IMPORT_CHECK_TARGETS MonetDB::stream )
list(APPEND _IMPORT_CHECK_FILES_FOR_MonetDB::stream "${_IMPORT_PREFIX}/lib/libstream.so.14.0.4" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
