# CMake generated Testfile for 
# Source directory: /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/ctest
# Build directory: /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/ctest
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestEcho "/usr/local/bin/cmake" "-E" "echo" "'MonetDB" "Testing'")
set_tests_properties(TestEcho PROPERTIES  _BACKTRACE_TRIPLES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/ctest/CMakeLists.txt;10;add_test;/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/ctest/CMakeLists.txt;0;")
subdirs("monetdb5")
subdirs("tools")
