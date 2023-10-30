#include "Logger.h"
#include <cstdio>
#include <cstdarg>

void Logger::Info(const char *format, ...) {
    if (m_LogLevel < LOG_INFO)
        return;

    fflush( stdout );
    va_list arg;
    va_start( arg, format );
    fprintf( stdout, "[INFO] ");
    vfprintf( stdout, format, arg );
    fflush( stdout );
    va_end( arg );
}

void Logger::Warning(const char *format, ...) {
    if (m_LogLevel < LOG_WARNING)
        return;

    fflush( stdout );
    va_list arg;
    va_start( arg, format );
    fprintf( stdout, "[WARNING] ");
    vfprintf( stdout, format, arg );
    fflush( stdout );
    va_end( arg );
}

void Logger::Debug(const char *format, ...) {
    if (m_LogLevel < LOG_DEBUG)
        return;

    fflush( stdout );
    va_list arg;
    va_start( arg, format );
    fprintf( stdout, "[DEBUG] ");
    vfprintf( stdout, format, arg );
    fflush( stdout );
    va_end( arg );
}

void Logger::Error(const char *format, ...) {
    fflush( stdout );
    va_list arg;
    va_start( arg, format );
    fprintf( stdout, "[ERROR] ");
    vfprintf( stdout, format, arg );
    fflush( stdout );
    va_end( arg );
}
