#include "logger.h"

#include <iostream>


int main() {
  
  Logger::log(LogLevel::INFO, "Server starting...");
  Logger::log(LogLevel::DEBUG, "Initializing components...");
  Logger::log(LogLevel::WARN, "No configuration file found, using defaults");
  Logger::log(LogLevel::ERROR, "Failed to bind to port 6379");
  
  return 0;
}