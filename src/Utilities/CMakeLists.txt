add_library(Logger SHARED Logger.cpp)
add_library(Timer SHARED Timer.cpp TimerControl.cpp)

if (SUPPORT_TIMER)
    target_compile_definitions(Timer PUBLIC SUPPORT_TIMER)
endif ()

install(TARGETS Timer DESTINATION lib)
install (TARGETS Logger DESTINATION lib)