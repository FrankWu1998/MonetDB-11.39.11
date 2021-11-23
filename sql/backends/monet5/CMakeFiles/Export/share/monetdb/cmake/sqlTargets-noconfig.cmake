#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MonetDB::sql" for configuration ""
set_property(TARGET MonetDB::sql APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MonetDB::sql PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmonetdbsql.so.11.39.11"
  IMPORTED_SONAME_NOCONFIG "libmonetdbsql.so.11"
  )

list(APPEND _IMPORT_CHECK_TARGETS MonetDB::sql )
list(APPEND _IMPORT_CHECK_FILES_FOR_MonetDB::sql "${_IMPORT_PREFIX}/lib/libmonetdbsql.so.11.39.11" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
