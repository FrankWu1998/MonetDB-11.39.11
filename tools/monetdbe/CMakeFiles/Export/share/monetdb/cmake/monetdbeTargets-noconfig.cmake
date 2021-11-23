#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MonetDB::monetdbe" for configuration ""
set_property(TARGET MonetDB::monetdbe APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MonetDB::monetdbe PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmonetdbe.so.1.0.2"
  IMPORTED_SONAME_NOCONFIG "libmonetdbe.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS MonetDB::monetdbe )
list(APPEND _IMPORT_CHECK_FILES_FOR_MonetDB::monetdbe "${_IMPORT_PREFIX}/lib/libmonetdbe.so.1.0.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
