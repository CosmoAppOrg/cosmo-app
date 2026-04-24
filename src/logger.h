#pragma once

#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

/**
 * @brief Sets up a multi-sink logger named "app".
 *
 * The logger has two sinks:
 *   1. A colored stdout sink (for console output with colors)
 *   2. A rotating file sink (5 MB max size, 3 files max)
 *
 * @return A shared pointer to the configured spdlog logger.
 */
inline std::shared_ptr<spdlog::logger> setup_logger() {
    // Create a logger with two sinks: stdout (colored) and a rotating file.
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink    = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "cosmoapp.log", 5 * 1024 * 1024, 3); // 5 MB, keep 3 files

    // Create the logger, initialized with both sinks.
    auto logger = std::make_shared<spdlog::logger>("app", spdlog::sinks_init_list{console_sink, file_sink});
    // Set the pattern (optional)
    logger->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] %v");
    // Set the log level (info by default)
    logger->set_level(spdlog::level::info);
    // Flush on every info (or you can set to flush on error, etc.)
    logger->flush_on(spdlog::level::info);

    return logger;
}