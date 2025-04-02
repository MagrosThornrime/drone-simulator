#pragma once
#include <string>
#include <chrono>
#include <utility>

enum LogLevel{info, warning, error};

class Logger{


    static void _logToFile(const std::string& text);
    static void _logToConsole(const std::string& text);
    static std::string _prepareMessage(const std::string& text);

public:

    inline static std::string path;
    inline static bool consoleUsed;
    inline static LogLevel level;
    static void log(const std::string& text, LogLevel level);

};