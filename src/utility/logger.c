#include "logger.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

void log(LogLevel level, const char* message) {
  printf("[%s] [%s] %s\n", level_to_string(level), get_timestamp(), message);
}

const char* level_to_string(LogLevel level) {
  switch (level) {
    case LOG_DEBUG: return "DEBUG";
    case LOG_ERROR: return "ERROR";
    case LOG_WARN: return "WARN";
    case LOG_INFO: return "INFO";
    
    default: return "UNKNOWN";
  }
}

const char* get_timestamp() {
  static char buffer[26];
  time_t current_time;
  time(&current_time);
  
  strftime(buffer, sizeof(buffer), "%H:%M:%S", localtime(&current_time));

  return buffer;
}