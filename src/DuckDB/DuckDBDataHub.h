#ifndef MYLIB_DUCKDBDATAHUB_H
#define MYLIB_DUCKDBDATAHUB_H

#include "duckdb.h"

duckdb_database db;
duckdb_connection con;

void PrintDuckDBVersion();
void InitializeDuckDB();
void FinalizeDuckDB();
void AppendDataToDuckDB();
void QueryDataFromDuckDB();
void DuckDBTestCreateData();
void DuckDBTestGetData();

#endif  // MYLIB_DUCKDBDATAHUB_H
