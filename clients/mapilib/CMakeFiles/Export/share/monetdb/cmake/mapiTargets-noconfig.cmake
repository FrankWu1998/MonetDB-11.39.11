#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MonetDB::mapi" for configuration ""
set_property(TARGET MonetDB::mapi APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MonetDB::mapi PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmapi.so.12.0.6"
  IMPORTED_SONAME_NOCONFIG "libmapi.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS MonetDB::mapi )
list(APPEND _IMPORT_CHECK_FILES_FOR_MonetDB::mapi "${_IMPORT_PREFIX}/lib/libmapi.so.12.0.6" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
