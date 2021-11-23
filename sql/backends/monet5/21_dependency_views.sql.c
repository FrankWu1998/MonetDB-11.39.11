unsigned char _21_dependency_views_sql[16378] = {
"CREATE VIEW sys.ids (id, name, schema_id, table_id, table_name, obj_type, sys_table) AS\n"
"SELECT id, name, cast(null as int) as schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, 'author' AS obj_type, 'sys.auths' AS sys_table FROM sys.auths UNION ALL\n"
"SELECT id, name, cast(null as int) as schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, 'schema', 'sys.schemas' FROM sys.schemas UNION ALL\n"
"SELECT id, name, schema_id, id as table_id, name as table_name, case when type = 1 then 'view' else 'table' end, 'sys._tables' FROM sys._tables UNION ALL\n"
"SELECT id, name, schema_id, id as table_id, name as table_name, case when type = 1 then 'view' else 'table' end, 'tmp._tables' FROM tmp._tables UNION ALL\n"
"SELECT c.id, c.name, t.schema_id, c.table_id, t.name as table_name, 'column', 'sys._columns' FROM sys._columns c JOIN sys._tables t ON c.table_id = t.id UNION ALL\n"
"SELECT c.id, c.name, t.schema_id, c.table_id, t.name as table_name, 'column', 'tmp._columns' FROM tmp._columns c JOIN tmp._tables t ON c.table_id = t.id UNION ALL\n"
"SELECT k.id, k.name, t.schema_id, k.table_id, t.name as table_name, 'key', 'sys.keys' FROM sys.keys k JOIN sys._tables t ON k.table_id = t.id UNION ALL\n"
"SELECT k.id, k.name, t.schema_id, k.table_id, t.name as table_name, 'key', 'tmp.keys' FROM tmp.keys k JOIN tmp._tables t ON k.table_id = t.id UNION ALL\n"
"SELECT i.id, i.name, t.schema_id, i.table_id, t.name as table_name, 'index', 'sys.idxs' FROM sys.idxs i JOIN sys._tables t ON i.table_id = t.id UNION ALL\n"
"SELECT i.id, i.name, t.schema_id, i.table_id, t.name as table_name, 'index', 'tmp.idxs' FROM tmp.idxs i JOIN tmp._tables t ON i.table_id = t.id UNION ALL\n"
"SELECT g.id, g.name, t.schema_id, g.table_id, t.name as table_name, 'trigger', 'sys.triggers' FROM sys.triggers g JOIN sys._tables t ON g.table_id = t.id UNION ALL\n"
"SELECT g.id, g.name, t.schema_id, g.table_id, t.name as table_name, 'trigger', 'tmp.triggers' FROM tmp.triggers g JOIN tmp._tables t ON g.table_id = t.id UNION ALL\n"
"SELECT id, name, schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, case when type = 2 then 'procedure' else 'function' end, 'sys.functions' FROM sys.functions UNION ALL\n"
"SELECT a.id, a.name, f.schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, case when f.type = 2 then 'procedure arg' else 'function arg' end, 'sys.args' FROM sys.args a JOIN sys.functions f ON a.func_id = f.id UNION ALL\n"
"SELECT id, name, schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, 'sequence', 'sys.sequences' FROM sys.sequences UNION ALL\n"
"SELECT id, sqlname, schema_id, cast(null as int) as table_id, cast(null as varchar(124)) as table_name, 'type', 'sys.types' FROM sys.types WHERE id > 2000\n"
"ORDER BY id;\n"
"GRANT SELECT ON sys.ids TO PUBLIC;\n"
"CREATE TABLE sys.dependency_types (\n"
"dependency_type_id SMALLINT NOT NULL PRIMARY KEY,\n"
"dependency_type_name VARCHAR(15) NOT NULL UNIQUE);\n"
"INSERT INTO sys.dependency_types (dependency_type_id, dependency_type_name) VALUES\n"
"(1, 'SCHEMA'),\n"
"(2, 'TABLE'),\n"
"(3, 'COLUMN'),\n"
"(4, 'KEY'),\n"
"(5, 'VIEW'),\n"
"(6, 'USER'),\n"
"(7, 'FUNCTION'),\n"
"(8, 'TRIGGER'),\n"
"(9, 'OWNER'),\n"
"(10, 'INDEX'),\n"
"(11, 'FKEY'),\n"
"(12, 'SEQUENCE'),\n"
"(13, 'PROCEDURE'),\n"
"(14, 'BE_DROPPED'),\n"
"(15, 'TYPE');\n"
"ALTER TABLE sys.dependency_types SET READ ONLY;\n"
"GRANT SELECT ON sys.dependency_types TO PUBLIC;\n"
"CREATE VIEW sys.dependencies_vw AS\n"
"SELECT d.id, i1.obj_type, i1.name,\n"
"d.depend_id as used_by_id, i2.obj_type as used_by_obj_type, i2.name as used_by_name,\n"
"d.depend_type, dt.dependency_type_name\n"
"FROM sys.dependencies d\n"
"JOIN sys.ids i1 ON d.id = i1.id\n"
"JOIN sys.ids i2 ON d.depend_id = i2.id\n"
"JOIN sys.dependency_types dt ON d.depend_type = dt.dependency_type_id\n"
"ORDER BY id, depend_id;\n"
"GRANT SELECT ON sys.dependencies_vw TO PUBLIC;\n"
"CREATE VIEW sys.dependency_owners_on_schemas AS\n"
"SELECT a.name AS owner_name, s.id AS schema_id, s.name AS schema_name, CAST(1 AS smallint) AS depend_type\n"
"FROM sys.schemas AS s, sys.auths AS a\n"
"WHERE s.owner = a.id\n"
"ORDER BY a.name, s.name;\n"
"GRANT SELECT ON sys.dependency_owners_on_schemas TO PUBLIC;\n"
"CREATE VIEW sys.dependency_columns_on_keys AS\n"
"SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, c.id AS column_id, c.name AS column_name, k.id AS key_id, k.name AS key_name, CAST(kc.nr +1 AS int) AS key_col_nr, CAST(k.type AS smallint) AS key_type, CAST(4 AS smallint) AS depend_type\n"
"FROM sys.columns AS c, sys.objects AS kc, sys.keys AS k, sys.tables AS t\n"
"WHERE k.table_id = c.table_id AND c.table_id = t.id AND kc.id = k.id AND kc.name = c.name\n"
"AND k.type IN (0, 1)\n"
"ORDER BY t.schema_id, t.name, c.name, k.type, k.name, kc.nr;\n"
"GRANT SELECT ON sys.dependency_columns_on_keys TO PUBLIC;\n"
"CREATE VIEW sys.dependency_tables_on_views AS\n"
"SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, v.schema_id AS view_schema_id, v.id AS view_id, v.name AS view_name, dep.depend_type AS depend_type\n"
"FROM sys.tables AS t, sys.tables AS v, sys.dependencies AS dep\n"
"WHERE t.id = dep.id AND v.id = dep.depend_id\n"
"AND dep.depend_type = 5 AND t.type NOT IN (1, 11) AND v.type IN (1, 11)\n"
"ORDER BY t.schema_id, t.name, v.schema_id, v.name;\n"
"GRANT SELECT ON sys.dependency_tables_on_views TO PUBLIC;\n"
"CREATE VIEW sys.dependency_views_on_views AS\n"
"SELECT v1.schema_id AS view1_schema_id, v1.id AS view1_id, v1.name AS view1_name, v2.schema_id AS view2_schema_id, v2.id AS view2_id, v2.name AS view2_name, dep.depend_type AS depend_type\n"
"FROM sys.tables AS v1, sys.tables AS v2, sys.dependencies AS dep\n"
"WHERE v1.id = dep.id AND v2.id = dep.depend_id\n"
"AND dep.depend_type = 5 AND v1.type IN (1, 11) AND v2.type IN (1, 11)\n"
"ORDER BY v1.schema_id, v1.name, v2.schema_id, v2.name;\n"
"GRANT SELECT ON sys.dependency_views_on_views TO PUBLIC;\n"
"CREATE VIEW sys.dependency_columns_on_views AS\n"
"SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, c.id AS column_id, c.name AS column_name, v.schema_id AS view_schema_id, v.id AS view_id, v.name AS view_name, dep.depend_type AS depend_type\n"
"FROM sys.columns AS c, sys.tables AS v, sys.tables AS t, sys.dependencies AS dep\n"
"WHERE c.id = dep.id AND v.id = dep.depend_id AND c.table_id = t.id\n"
"AND dep.depend_type = 5 AND v.type IN (1, 11)\n"
"ORDER BY t.schema_id, t.name, c.name, v.name;\n"
"GRANT SELECT ON sys.dependency_columns_on_views TO PUBLIC;\n"
"CREATE VIEW sys.dependency_functions_on_views AS\n"
"SELECT f.schema_id AS function_schema_id, f.id AS function_id, f.name AS function_name, v.schema_id AS view_schema_id, v.id AS view_id, v.name AS view_name, dep.depend_type AS depend_type\n"
"FROM sys.functions AS f, sys.tables AS v, sys.dependencies AS dep\n"
"WHERE f.id = dep.id AND v.id = dep.depend_id\n"
"AND dep.depend_type = 5 AND v.type IN (1, 11)\n"
"ORDER BY f.schema_id, f.name, v.schema_id, v.name;\n"
"GRANT SELECT ON sys.dependency_functions_on_views TO PUBLIC;\n"
"CREATE VIEW sys.dependency_schemas_on_users AS\n"
"SELECT s.id AS schema_id, s.name AS schema_name, u.name AS user_name, CAST(6 AS smallint) AS depend_type\n"
"FROM sys.users AS u, sys.schemas AS s\n"
"WHERE u.default_schema = s.id\n"
"ORDER BY s.name, u.name;\n"
"GRANT SELECT ON sys.dependency_schemas_on_users TO PUBLIC;\n"
"CREATE VIEW sys.dependency_tables_on_functions AS\n"
"SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, f.name AS function_name, f.type AS function_type, dep.depend_type AS depend_type\n"
"FROM sys.functions AS f, sys.tables AS t, sys.dependencies AS dep\n"
"WHERE t.id = dep.id AND f.id = dep.depend_id\n"
"AND dep.depend_type = 7 AND f.type <> 2 AND t.type NOT IN (1, 11)\n"
"ORDER BY t.name, t.schema_id, f.name, f.id;\n"
"GRANT SELECT ON sys.dependency_tables_on_functions TO PUBLIC;\n"
"CREATE VIEW sys.dependency_views_on_functions AS\n"
"SELECT v.schema_id AS view_schema_id, v.id AS view_id, v.name AS view_name, f.name AS function_name, f.type AS function_type, dep.depend_type AS depend_type\n"
"FROM sys.functions AS f, sys.tables AS v, sys.dependencies AS dep\n"
"WHERE v.id = dep.id AND f.id = dep.depend_id\n"
"AND dep.depend_type = 7 AND f.type <> 2 AND v.type IN (1, 11)\n"
"ORDER BY v.name, v.schema_id, f.name, f.id;\n"
"GRANT SELECT ON sys.dependency_views_on_functions TO PUBLIC;\n"
"CREATE VIEW sys.dependency_columns_on_functions AS\n"
"SELECT c.table_id, c.id AS column_id, c.name, f.id AS function_id, f.name AS function_name, f.type AS function_type, dep.depend_type AS depend_type\n"
"FROM sys.functions AS f, sys.columns AS c, sys.dependencies AS dep\n"
"WHERE c.id = dep.id AND f.id = dep.depend_id\n"
"AND dep.depend_type = 7 AND f.type <> 2\n"
"ORDER BY c.name, c.table_id, f.name, f.id;\n"
"GRANT SELECT ON sys.dependency_columns_on_functions TO PUBLIC;\n"
"CREATE VIEW sys.dependency_functions_on_functions AS\n"
"SELECT f1.schema_id, f1.id AS function_id, f1.name AS function_name, f1.type AS function_type,\n"
"f2.schema_id AS used_in_function_schema_id, f2.id AS used_in_function_id, f2.name AS used_in_function_name, f2.type AS used_in_function_type, dep.depend_type AS depend_type\n"
"FROM sys.functions AS f1, sys.functions AS f2, sys.dependencies AS dep\n"
"WHERE f1.id = dep.id AND f2.id = dep.depend_id\n"
"AND dep.depend_type = 7 AND f2.type <> 2\n"
"ORDER BY f1.name, f1.id, f2.name, f2.id;\n"
"GRANT SELECT ON sys.dependency_functions_on_functions TO PUBLIC;\n"
"CREATE VIEW sys.dependency_tables_on_triggers AS\n"
"(SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, tri.id AS trigger_id, tri.name AS trigger_name, CAST(8 AS smallint) AS depend_type\n"
"FROM sys.tables AS t, sys.triggers AS tri\n"
"WHERE tri.table_id = t.id)\n"
"UNION\n"
"(SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, tri.id AS trigger_id, tri.name AS trigger_name, dep.depend_type AS depend_type\n"
"FROM sys.tables AS t, sys.triggers AS tri, sys.dependencies AS dep\n"
"WHERE dep.id = t.id AND dep.depend_id = tri.id\n"
"AND dep.depend_type = 8)\n"
"ORDER BY table_schema_id, table_name, trigger_name;\n"
"GRANT SELECT ON sys.dependency_tables_on_triggers TO PUBLIC;\n"
"CREATE VIEW sys.dependency_columns_on_triggers AS\n"
"SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, tri.id AS trigger_id, tri.name AS trigger_name, c.id AS column_id, c.name AS column_name, dep.depend_type AS depend_type\n"
"FROM sys.tables AS t, sys.columns AS c, sys.triggers AS tri, sys.dependencies AS dep\n"
"WHERE dep.id = c.id AND dep.depend_id = tri.id AND c.table_id = t.id\n"
"AND dep.depend_type = 8\n"
"ORDER BY t.schema_id, t.name, tri.name, c.name;\n"
"GRANT SELECT ON sys.dependency_columns_on_triggers TO PUBLIC;\n"
"CREATE VIEW sys.dependency_functions_on_triggers AS\n"
"SELECT f.schema_id AS function_schema_id, f.id AS function_id, f.name AS function_name, f.type AS function_type,\n"
"tri.id AS trigger_id, tri.name AS trigger_name, tri.table_id AS trigger_table_id, dep.depend_type AS depend_type\n"
"FROM sys.functions AS f, sys.triggers AS tri, sys.dependencies AS dep\n"
"WHERE dep.id = f.id AND dep.depend_id = tri.id\n"
"AND dep.depend_type = 8\n"
"ORDER BY f.schema_id, f.name, tri.name;\n"
"GRANT SELECT ON sys.dependency_functions_on_triggers TO PUBLIC;\n"
"CREATE VIEW sys.dependency_tables_on_indexes AS\n"
"SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, i.id AS index_id, i.name AS index_name, i.type AS index_type, CAST(10 AS smallint) AS depend_type\n"
"FROM sys.tables AS t, sys.idxs AS i\n"
"WHERE i.table_id = t.id\n"
"AND (i.table_id, i.name) NOT IN (SELECT k.table_id, k.name FROM sys.keys k)\n"
"ORDER BY t.schema_id, t.name, i.name;\n"
"GRANT SELECT ON sys.dependency_tables_on_indexes TO PUBLIC;\n"
"CREATE VIEW sys.dependency_columns_on_indexes AS\n"
"SELECT c.id AS column_id, c.name AS column_name, t.id AS table_id, t.name AS table_name, t.schema_id, i.id AS index_id, i.name AS index_name, i.type AS index_type, CAST(ic.nr +1 AS INT) AS seq_nr, CAST(10 AS smallint) AS depend_type\n"
"FROM sys.tables AS t, sys.columns AS c, sys.objects AS ic, sys.idxs AS i\n"
"WHERE ic.name = c.name AND ic.id = i.id AND c.table_id = i.table_id AND c.table_id = t.id\n"
"AND (i.table_id, i.name) NOT IN (SELECT k.table_id, k.name FROM sys.keys k)\n"
"ORDER BY c.name, t.name, t.schema_id, i.name, ic.nr;\n"
"GRANT SELECT ON sys.dependency_columns_on_indexes TO PUBLIC;\n"
"CREATE VIEW sys.dependency_tables_on_foreignkeys AS\n"
"SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, fk.name AS fk_name, CAST(k.type AS smallint) AS key_type, CAST(11 AS smallint) AS depend_type\n"
"FROM sys.tables AS t, sys.keys AS k, sys.keys AS fk\n"
"WHERE fk.rkey = k.id and k.table_id = t.id\n"
"ORDER BY t.schema_id, t.name, fk.name;\n"
"GRANT SELECT ON sys.dependency_tables_on_foreignkeys TO PUBLIC;\n"
"CREATE VIEW sys.dependency_keys_on_foreignkeys AS\n"
"SELECT k.table_id AS key_table_id, k.id AS key_id, k.name AS key_name, fk.table_id AS fk_table_id, fk.id AS fk_id, fk.name AS fk_name, CAST(k.type AS smallint) AS key_type, CAST(11 AS smallint) AS depend_type\n"
"FROM sys.keys AS k, sys.keys AS fk\n"
"WHERE k.id = fk.rkey\n"
"ORDER BY k.name, fk.name;\n"
"GRANT SELECT ON sys.dependency_keys_on_foreignkeys TO PUBLIC;\n"
"CREATE VIEW sys.dependency_tables_on_procedures AS\n"
"SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, p.id AS procedure_id, p.name AS procedure_name, p.type AS procedure_type, dep.depend_type AS depend_type\n"
"FROM sys.functions AS p, sys.tables AS t, sys.dependencies AS dep\n"
"WHERE t.id = dep.id AND p.id = dep.depend_id\n"
"AND dep.depend_type = 13 AND p.type = 2 AND t.type NOT IN (1, 11)\n"
"ORDER BY t.name, t.schema_id, p.name, p.id;\n"
"GRANT SELECT ON sys.dependency_tables_on_procedures TO PUBLIC;\n"
"CREATE VIEW sys.dependency_views_on_procedures AS\n"
"SELECT v.schema_id AS view_schema_id, v.id AS view_id, v.name AS view_name, p.id AS procedure_id, p.name AS procedure_name, p.type AS procedure_type, dep.depend_type AS depend_type\n"
"FROM sys.functions AS p, sys.tables AS v, sys.dependencies AS dep\n"
"WHERE v.id = dep.id AND p.id = dep.depend_id\n"
"AND dep.depend_type = 13 AND p.type = 2 AND v.type IN (1, 11)\n"
"ORDER BY v.name, v.schema_id, p.name, p.id;\n"
"GRANT SELECT ON sys.dependency_views_on_procedures TO PUBLIC;\n"
"CREATE VIEW sys.dependency_columns_on_procedures AS\n"
"SELECT c.table_id, c.id AS column_id, c.name AS column_name, p.id AS procedure_id, p.name AS procedure_name, p.type AS procedure_type, dep.depend_type AS depend_type\n"
"FROM sys.functions AS p, sys.columns AS c, sys.dependencies AS dep\n"
"WHERE c.id = dep.id AND p.id = dep.depend_id\n"
"AND dep.depend_type = 13 AND p.type = 2\n"
"ORDER BY c.name, c.table_id, p.name, p.id;\n"
"GRANT SELECT ON sys.dependency_columns_on_procedures TO PUBLIC;\n"
"CREATE VIEW sys.dependency_functions_on_procedures AS\n"
"SELECT f.schema_id AS function_schema_id, f.id AS function_id, f.name AS function_name, f.type AS function_type,\n"
"p.schema_id AS procedure_schema_id, p.id AS procedure_id, p.name AS procedure_name, p.type AS procedure_type, dep.depend_type AS depend_type\n"
"FROM sys.functions AS p, sys.functions AS f, sys.dependencies AS dep\n"
"WHERE f.id = dep.id AND p.id = dep.depend_id\n"
"AND dep.depend_type = 13 AND p.type = 2\n"
"ORDER BY p.name, p.id, f.name, f.id;\n"
"GRANT SELECT ON sys.dependency_functions_on_procedures TO PUBLIC;\n"
"CREATE VIEW sys.dependency_columns_on_types AS\n"
"SELECT t.schema_id AS table_schema_id, t.id AS table_id, t.name AS table_name, dt.id AS type_id, dt.sqlname AS type_name, c.id AS column_id, c.name AS column_name, dep.depend_type AS depend_type\n"
"FROM sys.tables AS t, sys.columns AS c, sys.types AS dt, sys.dependencies AS dep\n"
"WHERE dep.id = dt.id AND dep.depend_id = c.id AND c.table_id = t.id\n"
"AND dep.depend_type = 15\n"
"ORDER BY dt.sqlname, t.name, c.name, c.id;\n"
"GRANT SELECT ON sys.dependency_columns_on_types TO PUBLIC;\n"
"CREATE VIEW sys.dependency_functions_on_types AS\n"
"SELECT dt.id AS type_id, dt.sqlname AS type_name, f.id AS function_id, f.name AS function_name, f.type AS function_type, dep.depend_type AS depend_type\n"
"FROM sys.functions AS f, sys.types AS dt, sys.dependencies AS dep\n"
"WHERE dep.id = dt.id AND dep.depend_id = f.id\n"
"AND dep.depend_type = 15\n"
"ORDER BY dt.sqlname, f.name, f.id;\n"
"GRANT SELECT ON sys.dependency_functions_on_types TO PUBLIC;\n"
"CREATE VIEW sys.dependency_args_on_types AS\n"
"SELECT dt.id AS type_id, dt.sqlname AS type_name, f.id AS function_id, f.name AS function_name, a.id AS arg_id, a.name AS arg_name, a.number AS arg_nr, dep.depend_type AS depend_type\n"
"FROM sys.args AS a, sys.functions AS f, sys.types AS dt, sys.dependencies AS dep\n"
"WHERE dep.id = dt.id AND dep.depend_id = a.id AND a.func_id = f.id\n"
"AND dep.depend_type = 15\n"
"ORDER BY dt.sqlname, f.name, a.number, a.name;\n"
"GRANT SELECT ON sys.dependency_args_on_types TO PUBLIC;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_21_dependency_views_sql)
{ sql_register("21_dependency_views", _21_dependency_views_sql); }