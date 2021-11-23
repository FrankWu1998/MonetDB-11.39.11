#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MonetDB::monetdb5" for configuration ""
set_property(TARGET MonetDB::monetdb5 APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MonetDB::monetdb5 PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmonetdb5.so.30.0.4"
  IMPORTED_SONAME_NOCONFIG "libmonetdb5.so.30"
  )

list(APPEND _IMPORT_CHECK_TARGETS MonetDB::monetdb5 )
list(APPEND _IMPORT_CHECK_FILES_FOR_MonetDB::monetdb5 "${_IMPORT_PREFIX}/lib/libmonetdb5.so.30.0.4" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
