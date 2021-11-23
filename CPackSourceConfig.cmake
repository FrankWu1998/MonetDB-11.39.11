# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "")
set(CPACK_BINARY_BUNDLE "")
set(CPACK_BINARY_CYGWIN "")
set(CPACK_BINARY_DEB "")
set(CPACK_BINARY_DRAGNDROP "")
set(CPACK_BINARY_FREEBSD "")
set(CPACK_BINARY_IFW "")
set(CPACK_BINARY_NSIS "")
set(CPACK_BINARY_NUGET "")
set(CPACK_BINARY_OSXX11 "")
set(CPACK_BINARY_PACKAGEMAKER "")
set(CPACK_BINARY_PRODUCTBUILD "")
set(CPACK_BINARY_RPM "")
set(CPACK_BINARY_STGZ "")
set(CPACK_BINARY_TBZ2 "")
set(CPACK_BINARY_TGZ "")
set(CPACK_BINARY_TXZ "")
set(CPACK_BINARY_TZ "")
set(CPACK_BINARY_WIX "")
set(CPACK_BINARY_ZIP "")
set(CPACK_BUILD_SOURCE_DIRS "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11;/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENTS_ALL "client;clientdev;clienttest;mclient;microbenchmark;monetdb;monetdbdev;odbc;pytesting;run_adder;run_isolate;run_memo;server;serverdev;sql;stream;streamdev;testing;tools")
set(CPACK_COMPONENT_CLIENTDEV_DESCRIPTION "MonetDB client/server interface library development files
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the files to develop with the libmonetdb-client12
 library.")
set(CPACK_COMPONENT_CLIENTTEST_DESCRIPTION "MonetDB client testing tools
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the sample MAPI programs used for testing other
 MonetDB packages.  You probably don't need this, unless you are a
 developer.")
set(CPACK_COMPONENT_CLIENT_DESCRIPTION "MonetDB client/server interface library
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains a shared library (libmapi) which is needed by
 various other components.")
set(CPACK_COMPONENT_FITS_DESCRIPTION "MonetDB5 SQL GIS support module
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains a module for accessing data in the FITS file
 format.")
set(CPACK_COMPONENT_GEOM_DESCRIPTION "MonetDB5 SQL GIS support module
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the GIS (Geographic Information System)
 extensions for MonetDB-SQL-server5.")
set(CPACK_COMPONENT_MCLIENT_DESCRIPTION "MonetDB database client
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains mclient, the main client program to communicate
 with the MonetDB database server, and msqldump, a program to dump the
 SQL database so that it can be loaded back later.  If you want to use
 MonetDB, you will very likely need this package.")
set(CPACK_COMPONENT_MONETDBDEV_DESCRIPTION "MonetDB development files
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains files needed to develop extensions to the core
 functionality of MonetDB.")
set(CPACK_COMPONENT_MONETDB_DESCRIPTION "MonetDB core library
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the core components of MonetDB in the form of a
 single shared library.  If you want to use MonetDB, you will certainly
 need this package, but you will also need at least the monetdb5-server
 package, and most likely also monetdb5-sql, as well as one or
 more client packages.")
set(CPACK_COMPONENT_ODBC_DESCRIPTION "MonetDB ODBC driver
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the MonetDB ODBC driver.")
set(CPACK_COMPONENT_PYAPI3_DESCRIPTION "Integration of MonetDB and Python, allowing use of Python from within SQL
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the interface to use the Python language from
 within SQL queries.  This package is for Python 3.
 .
 NOTE: INSTALLING THIS PACKAGE OPENS UP SECURITY ISSUES.  If you don't
 know how this package affects the security of your system, do not
 install it.")
set(CPACK_COMPONENT_PYTESTING_DESCRIPTION " Debugging symbols for monetdb packages
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the debugging symbols for all monetdb binary
 packages.")
set(CPACK_COMPONENT_RAPI_DESCRIPTION "Integration of MonetDB and R, allowing use of R from within SQL
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the interface to use the R language from within
 SQL queries.
 .
 NOTE: INSTALLING THIS PACKAGE OPENS UP SECURITY ISSUES.  If you don't
 know how this package affects the security of your system, do not
 install it.")
set(CPACK_COMPONENT_SERVERDEV_DESCRIPTION "MonetDB database server version 5
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains files needed to develop extensions that can be
 used from the MAL level.")
set(CPACK_COMPONENT_SERVER_DESCRIPTION "MonetDB database server version 5
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the MonetDB server component.  You need this
 package if you want to use the MonetDB database system.  If you want
 to use the SQL front end, you also need monetdb5-sql.")
set(CPACK_COMPONENT_SQL_DESCRIPTION "MonetDB SQL support for monetdb5
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the SQL front end for MonetDB.")
set(CPACK_COMPONENT_STREAMDEV_DESCRIPTION "MonetDB stream library development files
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the files to develop with the
 libmonetdb-stream14 library.")
set(CPACK_COMPONENT_STREAM_DESCRIPTION "MonetDB stream library
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains a shared library (libstream) which is needed by
 various other components.")
set(CPACK_COMPONENT_TESTING_DESCRIPTION "MonetDB testing programs
 MonetDB is a database management system that is developed from a
 main-memory perspective with use of a fully decomposed storage model,
 automatic index management, extensibility of data types and search
 accelerators.  It also has an SQL front end.
 .
 This package contains the programs and files needed for testing the
 MonetDB packages.  You probably don't need this, unless you are a
 developer.  If you do want to test, install monetdb-testing-python.")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_CLIENTDEV_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends}, libmonetdb-client12 (= \${source:Version}")
set(CPACK_DEBIAN_CLIENTDEV_PACKAGE_NAME "libmonetdb-client-dev")
set(CPACK_DEBIAN_CLIENTTEST_PACKAGE_DEPENDS "\${shlibs:Depends} ,libmonetdb-client-odbc (= \${source:Version}),
 monetdb5-server (= \${source:Version}),
 libdbd-monetdb-perl (>= 1.0),
 php-monetdb (>= 1.0),
 python3-pymonetdb (>= 1.0.6),
 monetdb5-sql (= \${source:Version})")
set(CPACK_DEBIAN_CLIENTTEST_PACKAGE_NAME "monetdb-client-testing")
set(CPACK_DEBIAN_CLIENT_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends}")
set(CPACK_DEBIAN_CLIENT_PACKAGE_NAME "libmonetdb-client12")
set(CPACK_DEBIAN_DEBUG_PACKAGE_DEPENDS "\${misc:Depends}")
set(CPACK_DEBIAN_DEBUG_PACKAGE_NAME "monetdb-dbg")
set(CPACK_DEBIAN_DEBUG_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_DEBUG_PACKAGE_SECTION "debug")
set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
set(CPACK_DEBIAN_FITS_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends}, monetdb5-sql (= \${source:Version}")
set(CPACK_DEBIAN_FITS_PACKAGE_NAME "libmonetdb5-server-cfitsio")
set(CPACK_DEBIAN_FITS_PACKAGE_SECTION "libs")
set(CPACK_DEBIAN_GEOM_PACKAGE_DEPENDS "\${shlibs:Depends}\${misc:Depends}, monetdb5-sql (= \${source:Version}")
set(CPACK_DEBIAN_GEOM_PACKAGE_NAME "libmonetdb5-server-geom")
set(CPACK_DEBIAN_GEOM_PACKAGE_SECTION "libs")
set(CPACK_DEBIAN_MCLIENT_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends}")
set(CPACK_DEBIAN_MCLIENT_PACKAGE_NAME "monetdb-client")
set(CPACK_DEBIAN_MCLIENT_PACKAGE_RECOMMENDS "monetdb5-sql (= \${source:Version}")
set(CPACK_DEBIAN_MONETDBDEV_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends}, libmonetdb21, libmonetdb-stream-dev")
set(CPACK_DEBIAN_MONETDBDEV_PACKAGE_NAME "libmonetdb-dev")
set(CPACK_DEBIAN_MONETDB_PACKAGE_CONFLICTS "libmonetdb5-server-geom (<< \${source:Version})")
set(CPACK_DEBIAN_MONETDB_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends}")
set(CPACK_DEBIAN_MONETDB_PACKAGE_NAME "libmonetdb21")
set(CPACK_DEBIAN_ODBC_PACKAGE_DEPENDS "\${shlibs:Depends}\${misc:Depends}")
set(CPACK_DEBIAN_ODBC_PACKAGE_NAME "libmonetdb-client-odbc")
set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS "OFF")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "MonetDB BV <info@monetdb.org>")
set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
set(CPACK_DEBIAN_PACKAGE_SOURCE "monetdb")
set(CPACK_DEBIAN_PYAPI3_PACKAGE_DEPENDS "\${shlibs:Depends};\${misc:Depends};monetdb5-sql (= \${source:Version});python3-numpy")
set(CPACK_DEBIAN_PYAPI3_PACKAGE_NAME "monetdb-python3")
set(CPACK_DEBIAN_PYTESTING_PACKAGE_DEPENDS "\${shlibs:Depends};\${misc:Depends};python3;monetdb-testing (= \${source:Version});monetdb-client-testing (= \${source:Version}")
set(CPACK_DEBIAN_PYTESTING_PACKAGE_NAME "monetdb-testing-python")
set(CPACK_DEBIAN_RAPI_PACKAGE_DEPENDS "\${shlibs:Depends};\${misc:Depends};monetdb5-sql (= \${source:Version});r-base-core")
set(CPACK_DEBIAN_RAPI_PACKAGE_NAME "monetdb-r")
set(CPACK_DEBIAN_SERVERDEV_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends},
 monetdb5-server (= \${source:Version}), libmonetdb-dev (= \${source:Version})")
set(CPACK_DEBIAN_SERVERDEV_PACKAGE_NAME "monetdb5-server-dev")
set(CPACK_DEBIAN_SERVER_PACKAGE_CONFLICTS "python-pymonetdb (<< 1.0.6)")
set(CPACK_DEBIAN_SERVER_PACKAGE_CONTROL_FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/debian/monetdb5-server.dirs;/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/debian/monetdb5-server.docs;/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/debian/monetdb5-server.manpages;/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/debian/monetdb5-server.postinst")
set(CPACK_DEBIAN_SERVER_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends}, adduser")
set(CPACK_DEBIAN_SERVER_PACKAGE_NAME "monetdb5-server")
set(CPACK_DEBIAN_SERVER_PACKAGE_SUGGESTS "monetdb-client (= \${source:Version})")
set(CPACK_DEBIAN_SQL_PACKAGE_CONTROL_FILES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/debian/monetdb5-sql.default;/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/debian/monetdb5-sql.dirs;/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/debian/monetdb5-sql.doc;/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/debian/monetdb5-sql.manpages;/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/debian/monetdb5-sql.postinst")
set(CPACK_DEBIAN_SQL_PACKAGE_DEPENDS "\${shlibs:Depends};\${misc:Depends};monetdb5-server (= \${source:Version})")
set(CPACK_DEBIAN_SQL_PACKAGE_NAME "monetdb5-sql")
set(CPACK_DEBIAN_SQL_PACKAGE_SUGGEST "monetdb-client (= \${source:Version})")
set(CPACK_DEBIAN_STREAMDEV_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends}, libmonetdb-stream14 (= \${source:Version}")
set(CPACK_DEBIAN_STREAMDEV_PACKAGE_NAME "libmonetdb-stream-dev")
set(CPACK_DEBIAN_STREAM_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends}")
set(CPACK_DEBIAN_STREAM_PACKAGE_NAME "libmonetdb-stream14")
set(CPACK_DEBIAN_TESTING_PACKAGE_DEPENDS "\${shlibs:Depends};\${misc:Depends}")
set(CPACK_DEBIAN_TESTING_PACKAGE_NAME "monetdb-testing")
set(CPACK_DEB_COMPONENT_INSTALL "ON")
set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_IGNORE_FILES "Tests;\\.hg;/test/;benchmarks")
set(CPACK_INSTALLED_DIRECTORIES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/cmake;/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/cmake/Modules")
set(CPACK_NSIS_DISPLAY_NAME "MonetDB 11.39.11")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "MonetDB 11.39.11")
set(CPACK_OUTPUT_CONFIG_FILE "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/local/share/cmake-3.15/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MonetDB built using CMake")
set(CPACK_PACKAGE_FILE_NAME "MonetDB-11.39.11-Source")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://www.monetdb.org/")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "MonetDB 11.39.11")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "MonetDB 11.39.11")
set(CPACK_PACKAGE_NAME "MonetDB")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "11.39.11")
set(CPACK_PACKAGE_VERSION_MAJOR "11")
set(CPACK_PACKAGE_VERSION_MINOR "39")
set(CPACK_PACKAGE_VERSION_PATCH "11")
set(CPACK_RESOURCE_FILE_LICENSE "/usr/local/share/cmake-3.15/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "/usr/local/share/cmake-3.15/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/local/share/cmake-3.15/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_BUILDREQUIRES "gcc, bison, /usr/bin/python3, /usr/lib/rpm/macros.d/macros.systemd, checkpolicy, selinux-policy-devel, hardlink, bzip2-devel, pkgconfig(libcurl), pkgconfig(liblzma), readline-devel, unixODBC-devel, pkgconfig(zlib), python3-devel >= 3.5, python3-numpy")
set(CPACK_RPM_CHANGELOG_FILE "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/misc/packages/rpm/changelog")
set(CPACK_RPM_COMPONENT_INSTALL "ON")
set(CPACK_RPM_PACKAGE_GROUP "Applications/Databases")
set(CPACK_RPM_PACKAGE_LICENSE "MPLv2.0")
set(CPACK_RPM_PACKAGE_RELOCATABLE "OFF")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_RPM_PACKAGE_SUMMARY "MonetDB - Monet Database Management System")
set(CPACK_RPM_PACKAGE_URL "https://www.monetdb.org/")
set(CPACK_RPM_PACKAGE_VENDOR "MonetDB BV <info@monetdb.org>")
set(CPACK_RPM_TESTING_PACKAGE_SUMMARY "MonetDB - Monet Database Management System")
set(CPACK_RPM_client_FILE_NAME "MonetDB-client-11.39.11.rpm")
set(CPACK_RPM_client_PACKAGE_NAME "client")
set(CPACK_RPM_client_PACKAGE_SUMMARY "MonetDB - Monet Database Management System Client Programs")
set(CPACK_RPM_client_RECCOMMENDS "%{name}-SQL-server5%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_clientdev_FILE_NAME "MonetDB-client-devel-11.39.11.rpm")
set(CPACK_RPM_clientdev_PACKAGE_NAME "client-devel")
set(CPACK_RPM_clientdev_PACKAGE_REQUIRES "%{name}-client%{?_isa} = %{version}-%{release}, %{name}-stream-devel%{?_isa} = %{version}-%{release}, openssl-devel")
set(CPACK_RPM_clientdev_PACKAGE_SUMMARY "MonetDB - Monet Database Management System Client Programs")
set(CPACK_RPM_clienttest_FILE_NAME "MonetDB-client-test-11.39.11.rpm")
set(CPACK_RPM_clienttest_PACKAGE_NAME "client-test")
set(CPACK_RPM_clienttest_PACKAGE_RECOMMENDS "perl-DBD-monetdb >= 1.0, php-monetdb >= 1.0")
set(CPACK_RPM_clienttest_PACKAGE_REQUIRES "MonetDB5-server%{?_isa} = %{version}-%{release}, %{name}-client%{?_isa} = %{version}-%{release}, %{name}-client-odbc%{?_isa} = %{version}-%{release}, %{name}-SQL-server5%{?_isa} = %{version}-%{release}, python3-pymonetdb >= 1.0.6")
set(CPACK_RPM_clienttest_PACKAGE_SUMMARY "MonetDB Client tests package")
set(CPACK_RPM_fits_FILE_NAME "MonetDB-cfitsio-11.39.11.rpm")
set(CPACK_RPM_fits_PACKAGE_NAME "cfitsio")
set(CPACK_RPM_fits_PACKAGE_REQUIRES "MonetDB-SQL-server5%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_fits_PACKAGE_SUMMARY "MonetDB: Add on module that provides support for FITS files")
set(CPACK_RPM_geom_FILE_NAME "MonetDB-geom-MonetDB5-11.39.11.rpm")
set(CPACK_RPM_geom_PACKAGE_NAME "geom-MonetDB5")
set(CPACK_RPM_geom_PACKAGE_REQUIRES "MonetDB5-server%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_geom_PACKAGE_SUMMARY "MonetDB5 SQL GIS support module")
set(CPACK_RPM_monetdb_FILE_NAME "MonetDB-11.39.11.rpm")
set(CPACK_RPM_monetdb_PACKAGE_NAME "MonetDB")
set(CPACK_RPM_monetdb_PACKAGE_SUGGESTS "%{name}-client%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_monetdbdev_FILE_NAME "MonetDB-devel-11.39.11.rpm")
set(CPACK_RPM_monetdbdev_PACKAGE_NAME "devel")
set(CPACK_RPM_monetdbdev_PACKAGE_REQUIRES "%{name}%{?_isa} = %{version}-%{release}, %{name}-stream-devel%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_monetdbdev_PACKAGE_SUMMARY "MonetDB development files")
set(CPACK_RPM_odbc_FILE_NAME "MonetDB-client-odbc-11.39.11.rpm")
set(CPACK_RPM_odbc_PACKAGE_NAME "client-odbc")
set(CPACK_RPM_odbc_PACKAGE_REQUIRES "%{name}-client%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_odbc_PACKAGE_REQUIRES_POST "unixODBC")
set(CPACK_RPM_odbc_PACKAGE_REQUIRES_POSTUN "unixODBC")
set(CPACK_RPM_odbc_PACKAGE_SUMMARY "MonetDB ODBC driver")
set(CPACK_RPM_pyapi3_FILE_NAME "MonetDB-python3-11.39.11.rpm")
set(CPACK_RPM_pyapi3_PACKAGE_NAME "python3")
set(CPACK_RPM_pyapi3_PACKAGE_REQUIRES "MonetDB-SQL-server5%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_pyapi3_PACKAGE_SUMMARY "Integration of MonetDB and Python, allowing use of Python from within SQL")
set(CPACK_RPM_pytesting_FILE_NAME "MonetDB-testing-python-11.39.11.rpm")
set(CPACK_RPM_pytesting_PACKAGE_ARCHITECTURE "noarch")
set(CPACK_RPM_pytesting_PACKAGE_NAME "testing-python")
set(CPACK_RPM_pytesting_PACKAGE_REQUIRES "%{name}-testing = %{version}-%{release}, %{name}-client-tests = %{version}-%{release}, /usr/bin/python3")
set(CPACK_RPM_pytesting_PACKAGE_SUMMARY "MonetDB - Monet Database Management System")
set(CPACK_RPM_rapi_FILE_NAME "MonetDB-R-11.39.11.rpm")
set(CPACK_RPM_rapi_PACKAGE_NAME "R")
set(CPACK_RPM_rapi_PACKAGE_REQUIRES "MonetDB-SQL-server5%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_rapi_PACKAGE_SUMMARY "Integration of MonetDB and R, allowing use of R from within SQL")
set(CPACK_RPM_selinux_FILE_NAME "MonetDB-selinux-11.39.11.rpm")
set(CPACK_RPM_selinux_PACKAGE_ARCHITECTURE "noarch")
set(CPACK_RPM_selinux_PACKAGE_NAME "selinux")
set(CPACK_RPM_selinux_PACKAGE_REQUIRES_POST "MonetDB5-server%{?_isa} = %{version}-%{release}, %{name}-SQL-server5%{?_isa} = %{version}-%{release}, /usr/sbin/semodule, /sbin/restorecon, /sbin/fixfiles")
set(CPACK_RPM_selinux_PACKAGE_REQUIRES_POSTUN "MonetDB5-server%{?_isa} = %{version}-%{release}, %{name}-SQL-server5%{?_isa} = %{version}-%{release}, /usr/sbin/semodule, /sbin/restorecon, /sbin/fixfiles")
set(CPACK_RPM_selinux_PACKAGE_SUMMARY "SELinux policy files for MonetDB")
set(CPACK_RPM_selinux_POST_INSTALL_SCRIPT_FILE "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/misc/selinux/post_install_script_file")
set(CPACK_RPM_selinux_POST_UNINSTALL_SCRIPT_FILE "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/misc/selinux/post_uninstall_script_file")
set(CPACK_RPM_server_FILE_NAME "MonetDB5-server-11.39.11.rpm")
set(CPACK_RPM_server_PACKAGE_CONFLICTS "python-pymonetdb < 1.0.6")
set(CPACK_RPM_server_PACKAGE_NAME "MonetDB5-server")
set(CPACK_RPM_server_PACKAGE_RECOMMENDS "%{name}-SQL-server5%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_server_PACKAGE_REQUIRES "%{name}-client%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_server_PACKAGE_REQUIRES_PRE "shadow-utils, systemd")
set(CPACK_RPM_server_PACKAGE_SUGGESTS "%{name}-client%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_server_PACKAGE_SUMMARY "MonetDB - Monet Database Management System")
set(CPACK_RPM_serverdev_FILE_NAME "MonetDB5-server-devel-11.39.11.rpm")
set(CPACK_RPM_serverdev_PACKAGE_NAME "MonetDB5-server-devel")
set(CPACK_RPM_serverdev_PACKAGE_REQUIRES "MonetDB5-server%{?_isa} = %{version}-%{release}, %{name}-devel%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_serverdev_PACKAGE_SUMMARY "MonetDB development files")
set(CPACK_RPM_sql_FILE_NAME "MonetDB-SQL-server5-11.39.11.rpm")
set(CPACK_RPM_sql_PACKAGE_NAME "SQL-server5")
set(CPACK_RPM_sql_PACKAGE_REQUIRES_PRE "MonetDB5-server%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_sql_PACKAGE_SUGGESTS "%{name}-client%{?_isa} = %{version}-%{release}")
set(CPACK_RPM_sql_PACKAGE_SUMMARY "MonetDB5 SQL server modules")
set(CPACK_RPM_stream_FILE_NAME "MonetDB-stream-11.39.11.rpm")
set(CPACK_RPM_stream_PACKAGE_NAME "stream")
set(CPACK_RPM_stream_SUMMARY "MonetDB stream library")
set(CPACK_RPM_streamdev_FILE_NAME "MonetDB-stream-devel-11.39.11.rpm")
set(CPACK_RPM_streamdev_PACKAGE_NAME "stream-devel")
set(CPACK_RPM_streamdev_REQUIRES "%{name}-stream%{?_isa} = %{version}-%{release}, bzip2-devel, libcurl-devel, zlib-devel")
set(CPACK_RPM_streamdev_SUMMARY "MonetDB stream library")
set(CPACK_RPM_testing_FILE_NAME "MonetDB-testing-11.39.11.rpm")
set(CPACK_RPM_testing_PACKAGE_NAME "testing")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "")
set(CPACK_SOURCE_CYGWIN "")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "Tests;\\.hg;/test/;benchmarks")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "MonetDB-11.39.11-Source")
set(CPACK_SOURCE_RPM "")
set(CPACK_SOURCE_TBZ2 "")
set(CPACK_SOURCE_TGZ "")
set(CPACK_SOURCE_TOPLEVEL_TAG "Linux-Source")
set(CPACK_SOURCE_TXZ "")
set(CPACK_SOURCE_TZ "")
set(CPACK_SOURCE_ZIP "")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_TOPLEVEL_TAG "Linux-Source")
set(CPACK_WIX_LICENSE_RTF "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/buildtools/conf/license.rtf")
set(CPACK_WIX_PRODUCT_ICON "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/buildtools/conf/monetdb.ico")
set(CPACK_WIX_SIZEOF_VOID_P "8")
set(CPACK_WIX_UI_DIALOG "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/buildtools/conf/banner.bmp")
set(CPACK_WIX_UPGRADE_GUID "DA9D1C50-3589-44F2-B5DA-FE95D7F3E271")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
