#include <Logger.h>
#include <sstream>
#include <fstream>
#include <iostream>

std::string Logger::_prepareMessage(const std::string &text) {
    auto now = std::chrono::system_clock::now();
    std::stringstream stream;
    stream << now << " : " << text;
    return stream.str();

}

void Logger::_logToConsole(const std::string &text) {
    std::cout << text << std::endl;
}

void Logger::_logToFile(const std::string &text) {
    std::ofstream logFile;

    logFile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    try{
        logFile.open(path.c_str(), std::ios_base::app);
        logFile << text << std::endl;
        logFile.close();
    }
    catch(std::ofstream::failure& e) {
        _logToConsole(_prepareMessage("failed to log to file"));
    }
}

void Logger::log(const std::string &text, LogLevel currentLevel) {
    if(currentLevel == warning and level == info)
        return;
    if(currentLevel == error and level != error)
        return;

    std::string toLog = _prepareMessage(text);
    if(consoleUsed)
        _logToConsole(toLog);
    if(!path.empty())
        _logToFile(toLog);
}