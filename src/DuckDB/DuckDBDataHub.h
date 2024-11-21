#ifndef MYLIB_DUCKDBDATAHUB_H
#define MYLIB_DUCKDBDATAHUB_H

#include <string>
#include <vector>

#include "../LibraryAPI/library.h"
#include "duckdb.h"

duckdb_database db;
duckdb_connection con;

void PrintDuckDBVersion();
void InitializeDuckDB();
void FinalizeDuckDB();
void AppendDataToDuckDB(const std::vector<simu_data>& wrapped_pointers);
void QueryDataFromDuckDB(std::vector<simu_data>& query_data);
void DuckDBTestCreateData();
void ClearDataInDataHub();
void DuckDBTestGetData();

#endif  // MYLIB_DUCKDBDATAHUB_H
