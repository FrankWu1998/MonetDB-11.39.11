file(REMOVE_RECURSE
  "libmonetdb5.pdb"
  "libmonetdb5.so"
  "libmonetdb5.so.30"
  "libmonetdb5.so.30.0.4"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/monetdb5.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
