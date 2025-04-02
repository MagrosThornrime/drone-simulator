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

    static std::string path;
    static bool consoleUsed;
    static LogLevel level;
    static void log(const std::string& text, LogLevel level);

};