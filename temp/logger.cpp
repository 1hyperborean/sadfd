#include "logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>

void Logger::log(LogLevel level, const std::string& message) {
  std::cout << "[" << getTimestamp() << "] "
            << "[" << levelToString(level) << "] "
            << message << std::endl;
}

std::string Logger::getTimestamp() {
  auto now = std::chrono::system_clock::now();
  auto time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
  return ss.str();
}

std::string Logger::levelToString(LogLevel level) {
  switch (level) {
    case LogLevel::DEBUG: return "DEBUG";
    case LogLevel::ERROR: return "ERROR";
    case LogLevel::INFO: return "INFO";
    case LogLevel::WARN: return "WARN";
    default: return "UNKNOWN";
  }
}