#pragma once

#include <iostream>
#include <string>

enum class LogLevel {
  DEBUG, INFO, WARN, ERROR
};

class Logger {
public:
  static void log(LogLevel level, const std::string& message);
  static std::string levelToString(LogLevel level);
  static std::string getTimestamp();
};