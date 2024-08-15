#ifndef MYLIB_TIMER_H
#define MYLIB_TIMER_H

#ifdef SUPPORT_TIMER
#include <chrono>

#include "TimerControl.h"

class Timer {
public:
    Timer(const char* func_name, TimerControl* timerControl);

    ~Timer();
    void Stop();

private:
    const char* m_FuncName;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    bool m_Stopped;
    TimerControl* m_TimerControlPtr;
};
#endif  // #ifdef SUPPORT_TIMER

#ifdef SUPPORT_TIMER
#define SET_TIMER(x, y) Timer Timer(x, y)
#else
#define SET_TIMER(x, y)
#endif  // #ifdef SUPPORT_TIMER

#endif  // MYLIB_TIMER_H
