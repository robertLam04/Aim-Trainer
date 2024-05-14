#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>
#include <memory>

// Declare the logger as an external variable
extern std::shared_ptr<spdlog::logger> console;

#endif // LOGGER_H