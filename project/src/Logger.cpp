#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

// Define the logger
std::shared_ptr<spdlog::logger> console = spdlog::stdout_color_mt("console");