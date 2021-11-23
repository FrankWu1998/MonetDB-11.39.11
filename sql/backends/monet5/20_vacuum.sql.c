unsigned char _20_vacuum_sql[221] = {
"create procedure shrink(sys string, tab string)\n"
"external name sql.shrink;\n"
"create procedure reuse(sys string, tab string)\n"
"external name sql.reuse;\n"
"create procedure vacuum(sys string, tab string)\n"
"external name sql.vacuum;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_20_vacuum_sql)
{ sql_register("20_vacuum", _20_vacuum_sql); }
