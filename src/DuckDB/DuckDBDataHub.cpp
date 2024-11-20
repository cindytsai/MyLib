#ifdef USE_DUCKDB

#include "DuckDBDataHub.h"
#include <iostream>
#include <string>
#include <vector>


void PrintDuckDBVersion() {
    std::cout << "[DuckDB] DuckDB version: " << duckdb_library_version() << std::endl;
}

void InitializeDuckDB() {
    if (duckdb_open(nullptr, &db) == DuckDBError) {
        std::cout << "[DuckDB] Failed to open database" << std::endl;
    }

    // With the duckdb_database handle, you can create one or many duckdb_connection using duckdb_connect().
    // While individual connections are thread-safe, they will be locked during querying.
    // It is therefore recommended that each thread uses its own connection to allow for the best parallel performance.
    // HERE, try single-threaded connection first.
    if (duckdb_connect(db, &con) == DuckDBError) {
        std::cout << "[DuckDB] Failed to connect to database" << std::endl;
    }
    std::cout << "[DuckDB] In-memory database initialized and connected" << std::endl;

    // Create DataHub table
    void *p;
    if (sizeof(p) > 8) {
        std::cout << "[DuckDB] Table cannot store pointer, change to larger data type" << std::endl;
    }
    std::string query = "CREATE TABLE data_hub (grid_id INTEGER PRIMARY KEY, name VARCHAR(20), data_ptr BIGINT);";
    duckdb_state db_state = duckdb_query(con, query.c_str(), nullptr);
    if (db_state == DuckDBError) {
        std::cout << "[DuckDB] Cannot create table data_hub" << std::endl;
    }

    std::cout << "[DuckDB] data_hub(INTEGER grid_id, VARCHAR(20) name, BIGINT data_ptr) table created" << std::endl;

    // Insert test data
//    double *data_ptr = new double[10]; // TODO: not freed, testing purpose only
//    uintptr_t addr = reinterpret_cast<uintptr_t>(data_ptr);
//    for (int i = 0; i < 10; i++) {
//        data_ptr[i] = i * 100 + 100;
//    }
//    std::cout << "[DuckDB] data_ptr[0] = " << data_ptr[0] << std::endl;
//    std::cout << "[DuckDB] addr[0] = " << reinterpret_cast<double*>(addr)[0] << std::endl;
//
//    duckdb_prepared_statement stmt;
//    duckdb_result result;
//    if (duckdb_prepare(con, "INSERT INTO data_hub VALUES ($1, $2, $3)", &stmt) == DuckDBError) {
//        std::cout << "[DuckDB] Unable to prepare statement" << std::endl;
//    }
//    duckdb_bind_int32(stmt, 1, 1);
//    duckdb_bind_varchar_length(stmt, 2, "test", 4);
//    duckdb_bind_uint64(stmt, 3, addr);
//
//    duckdb_execute_prepared(stmt, &result);
//    duckdb_destroy_result(&result);
//
//    duckdb_bind_int32(stmt, 1, 2);
//    duckdb_bind_varchar_length(stmt, 2, "test2", 4);
//    duckdb_bind_uint64(stmt, 3, 0);
//
//    duckdb_execute_prepared(stmt, &result);
//    duckdb_destroy_result(&result);
//    duckdb_destroy_prepare(&stmt);
//
//    std::cout << "[DuckDB] Data inserted into data_hub" << std::endl;
//
//    // Query test data
//    query = "SELECT * FROM data_hub;";
//    db_state = duckdb_query(con, query.c_str(), &result);
//    if (db_state == DuckDBError) {
//        std::cout << "[DuckDB] Query failed" << std::endl;
//    }
//
//    while (true) {
//        // Loop through results
//        duckdb_data_chunk data_chunk = duckdb_fetch_chunk(result);
//        if (!data_chunk) {
//            break;
//        }
//
//        // Get number of rows from the data chunk
//        idx_t row_count = duckdb_data_chunk_get_size(data_chunk);
//        std::cout << "Row count: " << row_count << std::endl;
//
//        // Get column
//        duckdb_vector col1 = duckdb_data_chunk_get_vector(data_chunk, 0);
//        int32_t *col1_data = (int32_t *)duckdb_vector_get_data(col1);
//        duckdb_type col1_type = duckdb_column_type(&result, 0);
//
//        duckdb_vector col2 = duckdb_data_chunk_get_vector(data_chunk, 1);
//        duckdb_string_t *col2_data = (duckdb_string_t *)duckdb_vector_get_data(col2);
//        duckdb_type col2_type = duckdb_column_type(&result, 1);
//
//        duckdb_vector col3 = duckdb_data_chunk_get_vector(data_chunk, 2);
//        uint64_t *col3_data = (uint64_t *)duckdb_vector_get_data(col3);
//        duckdb_type col3_type = duckdb_column_type(&result, 2);
//
//        std::cout << "Column type: " << col1_type << ", " << col2_type << ", " << col3_type << std::endl;
//
//        // Print value
//        std::cout << col1_data[0];
//        if (duckdb_string_is_inlined(col2_data[0])) {
//            std::cout << " " << col2_data[0].value.inlined.inlined << "(is_inline)";
//        } else {
//            std::cout << " " << col2_data[0].value.pointer.ptr << "(is_pointer)";
//        }
//        std::cout << " " << col3_data[0];
//        std::cout << "( value data_ptr[0] = " << reinterpret_cast<double*>(col3_data[0])[0] << " )" << std::endl;
//
//        // Destroy data chunk
//        duckdb_destroy_data_chunk(&data_chunk);
//    }
//
//    duckdb_destroy_result(&result);
}

void DuckDBTestCreateData() {
    std::cout << "[DuckDB] Creating data ..." << std::endl;

    duckdb_state db_state;
    duckdb_result db_result;
    std::string query = "CREATE TABLE integers (i INTEGER, j INTEGER);"
                        "INSERT INTO integers VALUES (3, 4), (5, 6), (7, NULL);";
    db_state = duckdb_query(con, query.c_str(), &db_result);

    if (db_state == DuckDBError) {
        std::cout << "[DuckDB] Query failed" << std::endl;
    } else {
        std::cout << "[DuckDB] Query succeeded" << std::endl;
    }

    // destroy the result after we are done with it
    duckdb_destroy_result(&db_result);
}

void DuckDBTestGetData() {
    std::cout << "[DuckDB] Getting data ..." << std::endl;

    duckdb_state db_state;
    duckdb_result db_result;
    std::string query = "SELECT * FROM integers;";
    db_state = duckdb_query(con, query.c_str(), &db_result);
    if (db_state == DuckDBError) {
        std::cout << "[DuckDB] " << duckdb_result_error(&db_result) << std::endl;
    }

    while (true) {
        // Loop through results
        duckdb_data_chunk data_chunk = duckdb_fetch_chunk(db_result);
        if (!data_chunk) {
            break;
        }

        // Get number of rows from the data chunk
        idx_t row_count = duckdb_data_chunk_get_size(data_chunk);
        std::cout << "Row count: " << row_count << std::endl;

        // Get column
        duckdb_vector col1 = duckdb_data_chunk_get_vector(data_chunk, 0);
        int32_t *col1_data = (int32_t *)duckdb_vector_get_data(col1);
        uint64_t *col1_validity = duckdb_vector_get_validity(col1);
        duckdb_type col1_type = duckdb_column_type(&db_result, 0);

        duckdb_vector col2 = duckdb_data_chunk_get_vector(data_chunk, 1);
        int32_t *col2_data = (int32_t *)duckdb_vector_get_data(col2);
        uint64_t *col2_validity = duckdb_vector_get_validity(col2);
        duckdb_type col2_type = duckdb_column_type(&db_result, 1);

        // Print column type
        std::cout << col1_type << ", " << col2_type << std::endl;
        std::cout << duckdb_column_name(&db_result, 0) << ", " << duckdb_column_name(&db_result, 1) << std::endl;

        // Print data chunk row by row
        for (idx_t i = 0; i < row_count; i++) {
            std::cout << "# " << i << ": ";

            if (duckdb_validity_row_is_valid(col1_validity, i)) {
                std::cout << col1_data[i] << " ";
            } else {
                std::cout << "NULL ";
            }

            if (duckdb_validity_row_is_valid(col2_validity, i)) {
                std::cout << col2_data[i] << std::endl;
            } else {
                std::cout << "NULL" << std::endl;
            }
            std::cout << std::endl;
        }

        // Destroy data chunk
        duckdb_destroy_data_chunk(&data_chunk);
    }

    // destroy the result after we are done with it, must call it even if query fails
    // otherwise the error and the result will not be freed correctly
    duckdb_destroy_result(&db_result);
}

void AppendDataToDuckDB(const std::vector<simu_data> &wrapped_pointers) {
    std::cout << "[DuckDB] Appending data ..." << std::endl;

    duckdb_appender appender;
    if (duckdb_appender_create(con, nullptr, "data_hub", &appender) == DuckDBError) {
        std::cout << "[DuckDB] Unable to create appender" << std::endl;
    }

    for (const auto &simu_data : wrapped_pointers) {
        duckdb_append_int32(appender, (int) simu_data.gid);
        duckdb_append_varchar(appender, simu_data.name);
        duckdb_append_uint64(appender, reinterpret_cast<uintptr_t>(simu_data.data_ptr));
        duckdb_appender_end_row(appender);
    }

    // finish appending and flush all the rows to the table
    duckdb_appender_destroy(&appender);
}

void QueryDataFromDuckDB() {
    
}

void ClearDataInDataHub() {
    std::cout << "[DuckDB] Clearing all records in data_hub ..." << std::endl;

    std::string query = "DELETE FROM data_hub;";
    duckdb_state  db_state = duckdb_query(con, query.c_str(), nullptr);
    if (db_state == DuckDBError) {
        std::cout << "[DuckDB] Query failed" << std::endl;
    }
}

void FinalizeDuckDB() {
    duckdb_disconnect(&con);
    duckdb_close(&db);

    std::cout << "[DuckDB] In-memory database disconnected and finalized" << std::endl;
}

#endif