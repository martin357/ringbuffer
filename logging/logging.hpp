#pragma once

#include <cstdio>

class Logging {
public:
    /// @brief Supported logging levels
    enum class Level {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
    };

    /// @brief Set the logging level
    static void SetLoggingLevel(Level level) {
        current_level = level;
    }

    /// @brief Log a formatted message with info level
    template <typename... Args>
    static void Info(const char *format, Args... args) {
        if (current_level <= Level::INFO) {
            Log(Level::INFO, format, args...);
        }
    }

    /// @brief Log a formatted message with debug level
    template <typename... Args>
    static void Debug(const char *format, Args... args) {
        if (current_level <= Level::DEBUG) {
            Log(Level::DEBUG, format, args...);
        }
    }

    /// @brief Log a formatted message with warn level
    template <typename... Args>
    static void Warning(const char *format, Args... args) {
        if (current_level <= Level::WARN) {
            Log(Level::WARN, format, args...);
        }
    }

    /// @brief Log a formatted message with error level
    template <typename... Args>
    static void Error(const char *format, Args... args) {
        if (current_level <= Level::ERROR) {
            Log(Level::ERROR, format, args...);
        }
    }

    /// @brief Log a formatted message with fatal level
    template <typename... Args>
    static void Fatal(const char *format, Args... args) {
        if (current_level <= Level::FATAL) {
            Log(Level::FATAL, format, args...);
        }
    }

private:
    inline static Level current_level = Level::DEBUG;

    static void write_newline() {
        printf("\r\n");
    }

    static void write_prefix(Level level) {
        switch (level) {
            case Level::DEBUG:
                printf("[DEBUG] ");
                break;
            case Level::INFO:
                printf("[INFO] ");
                break;
            case Level::WARN:
                printf("[WARN] ");
                break;
            case Level::ERROR:
                printf("[ERROR] ");
                break;
            case Level::FATAL:
                printf("[FATAL] ");
                break;
            default:
                printf("[UNKNOWN] ");
        }
    }

    template <typename... Args>
    static void Log(Level level, const char *format, Args... args) {
        write_prefix(level);
        printf(format, args...);
        write_newline();
    }

    static void Log(Level level, const char *format) {
        write_prefix(level);
        printf("%s", format);
        write_newline();
    }
};
