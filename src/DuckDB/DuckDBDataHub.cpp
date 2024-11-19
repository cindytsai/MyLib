#ifdef USE_DUCKDB

#include "DuckDBDataHub.h"
#include <iostream>
#include <string>

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

void AppendDataToDuckDB() {

}

void QueryDataFromDuckDB() {

}

void FinalizeDuckDB() {
    duckdb_disconnect(&con);
    duckdb_close(&db);

    std::cout << "[DuckDB] In-memory database disconnected and finalized" << std::endl;
}

#endif