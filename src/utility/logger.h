#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
  LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR
} LogLevel;

void log(LogLevel level, const char* message);
const char* level_to_string(LogLevel level);
const char* get_timestamp();

#endif