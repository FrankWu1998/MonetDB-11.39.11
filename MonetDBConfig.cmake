#[[
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0.  If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# Copyright 1997 - July 2008 CWI, August 2008 - 2021 MonetDB B.V.
#]]


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was Config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

####################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/monetdb_config_headerTargets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/streamTargets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/mapiTargets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/matomicTargets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/mstringTargets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/gdkTargets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/monetdb5Targets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/sqlTargets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/monetdbeTargets.cmake")
