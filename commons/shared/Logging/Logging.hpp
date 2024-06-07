#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <memory>
#include <sstream>

#define LOG_INFO(message) Logger::GetInstance().Log(LogLevel::INFO, message)
#define LOG_WARNING(message) Logger::GetInstance().Log(LogLevel::WARNING, message)
#define LOG_ERROR(message) Logger::GetInstance().Log(LogLevel::ERROR, message)
#define LOG_DEBUG(message) Logger::GetInstance().Log(LogLevel::DEBUG, message)


enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};


class Logger {
public:
    static Logger& GetInstance() {
        static Logger instance;
        return instance;
    }

    void SetLogLevel(LogLevel level) {
        m_LogLevel = level;
    }

    void SetOutputFile(const std::string& filename) {
        std::lock_guard<std::mutex> lock(m_LogMutex);
        if (m_LogFile.is_open()) {
            m_LogFile.close();
        }
        m_LogFile.open(filename, std::ios_base::app);
    }

    void Log(LogLevel level, const std::string& message) {
        if (level >= m_LogLevel) {
            std::lock_guard<std::mutex> lock(m_LogMutex);
            std::string colorCode = GetColorCode(level);
            std::string resetCode = "\033[0m";
            std::string boldCode = "\033[1m";
            std::ostringstream oss;
            oss << colorCode << boldCode << "[" << LogLevelToString(level) << "] " << resetCode << colorCode << message << resetCode << std::endl;
            std::string logMessage = oss.str();
            if (m_LogFile.is_open()) {
                m_LogFile << "[" << LogLevelToString(level) << "] " << message << std::endl;
                std::cout << logMessage;
            } else {
                std::cout << logMessage;
            }
        }
    }

private:
    LogLevel m_LogLevel = LogLevel::INFO;
    std::ofstream m_LogFile;
    std::mutex m_LogMutex;

    Logger() {}
    ~Logger() {
        if (m_LogFile.is_open()) {
            m_LogFile.close();
        }
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string LogLevelToString(LogLevel level) {
        switch (level) {
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::DEBUG: return "DEBUG";
            default: return "UNKNOWN";
        }
    }

    std::string GetColorCode(LogLevel level) {
        switch (level) {
        case LogLevel::INFO: return "\033[32m";    // Green
        case LogLevel::WARNING: return "\033[33m"; // Yellow
        case LogLevel::ERROR: return "\033[31m";   // Red
        case LogLevel::DEBUG: return "\033[34m";   // Blue
        default: return "\033[0m";                 // Reset
        }
    }
};