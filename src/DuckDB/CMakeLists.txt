add_library(DuckDB DuckDBDataHub.cpp)

if (USE_DUCKDB)
    target_compile_definitions(DuckDB PUBLIC USE_DUCKDB)
    target_include_directories(DuckDB PUBLIC ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(DuckDB PUBLIC ${DUCKDB_PATH}/lib/libduckdb.so)
    target_include_directories(DuckDB PUBLIC ${DUCKDB_PATH}/include)
endif()
