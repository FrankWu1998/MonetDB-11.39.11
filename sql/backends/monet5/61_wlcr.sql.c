unsigned char _61_wlcr_sql[847] = {
"create schema wlr;\n"
"create procedure wlr.master(dbname string)\n"
"external name wlr.master;\n"
"create procedure wlr.stop()\n"
"external name wlr.stop;\n"
"create procedure wlr.accept()\n"
"external name wlr.accept;\n"
"create procedure wlr.replicate()\n"
"external name wlr.replicate;\n"
"create procedure wlr.replicate(pointintime timestamp)\n"
"external name wlr.replicate;\n"
"create procedure wlr.replicate(id tinyint)\n"
"external name wlr.replicate;\n"
"create procedure wlr.replicate(id smallint)\n"
"external name wlr.replicate;\n"
"create procedure wlr.replicate(id integer)\n"
"external name wlr.replicate;\n"
"create procedure wlr.replicate(id bigint)\n"
"external name wlr.replicate;\n"
"create procedure wlr.beat(duration integer)\n"
"external name wlr.\"setbeat\";\n"
"create function wlr.clock() returns string\n"
"external name wlr.\"getclock\";\n"
"create function wlr.tick() returns bigint\n"
"external name wlr.\"gettick\";\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_61_wlcr_sql)
{ sql_register("61_wlcr", _61_wlcr_sql); }
