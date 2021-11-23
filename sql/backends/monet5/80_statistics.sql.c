unsigned char _80_statistics_sql[641] = {
"CREATE TABLE sys.statistics(\n"
"\"column_id\" integer,\n"
"\"type\" string,\n"
"width integer,\n"
"stamp timestamp,\n"
"\"sample\" bigint,\n"
"\"count\" bigint,\n"
"\"unique\" bigint,\n"
"\"nils\" bigint,\n"
"minval string,\n"
"maxval string,\n"
"sorted boolean,\n"
"revsorted boolean);\n"
"create procedure sys.analyze(minmax int, \"sample\" bigint)\n"
"external name sql.analyze;\n"
"create procedure sys.analyze(minmax int, \"sample\" bigint, sch string)\n"
"external name sql.analyze;\n"
"create procedure sys.analyze(minmax int, \"sample\" bigint, sch string, tbl string)\n"
"external name sql.analyze;\n"
"create procedure sys.analyze(minmax int, \"sample\" bigint, sch string, tbl string, col string)\n"
"external name sql.analyze;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_80_statistics_sql)
{ sql_register("80_statistics", _80_statistics_sql); }
