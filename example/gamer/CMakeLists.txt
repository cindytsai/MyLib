add_executable(GamerMock gamer_mock.cpp)

# link lib
target_include_directories(GamerMock PUBLIC ../../src/LibraryAPI)
target_link_libraries(GamerMock PUBLIC MyLib)
configure_file(hier.txt ${CMAKE_CURRENT_BINARY_DIR}/hier.txt COPYONLY)
configure_file(inline_script.py ${CMAKE_CURRENT_BINARY_DIR}/inline_script.py COPYONLY)