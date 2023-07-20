### Example ###
# Equivalent to: g++ -I../include example.cpp -L../lib -lMyLib -Wl,-rpath,../lib
add_executable(example example.cpp)
target_include_directories(example PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(example PUBLIC MyLib)
