#ifndef MYLIB_LOGGING_H
#define MYLIB_LOGGING_H

#include "LogLevel.h"

class Logger {
private:
    log_level m_LogLevel;
public:
    Logger(log_level level) : m_LogLevel(level) {}
    void SetLevel(log_level level) {m_LogLevel = level;}
    void Info( const char *format, ... );
    void Warning( const char *format, ... );
    void Debug( const char *format, ... );
    void Error( const char *format, ... );
};

#endif //MYLIB_LOGGING_H
