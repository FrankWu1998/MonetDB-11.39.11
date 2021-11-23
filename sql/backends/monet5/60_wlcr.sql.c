unsigned char _60_wlcr_sql[463] = {
"create schema wlc;\n"
"create procedure wlc.master()\n"
"external name wlc.master;\n"
"create procedure wlc.master(path string)\n"
"external name wlc.master;\n"
"create procedure wlc.stop()\n"
"external name wlc.stop;\n"
"create procedure wlc.flush()\n"
"external name wlc.flush;\n"
"create procedure wlc.beat( duration int)\n"
"external name wlc.\"setbeat\";\n"
"create function wlc.clock() returns string\n"
"external name wlc.\"getclock\";\n"
"create function wlc.tick() returns bigint\n"
"external name wlc.\"gettick\";\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_60_wlcr_sql)
{ sql_register("60_wlcr", _60_wlcr_sql); }
