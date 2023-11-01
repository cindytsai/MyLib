find_package(Python COMPONENTS Development NumPy)

add_library(PythonCore SHARED PythonCore.cpp)

if (USE_BOO)
    target_compile_definitions(PythonCore PUBLIC USE_BOO)
endif ()

target_include_directories(PythonCore PUBLIC ${Python_INCLUDE_DIRS})
target_link_libraries(PythonCore PUBLIC ${Python_LIBRARIES})
target_link_libraries(PythonCore PUBLIC mylib_compiler_flags)