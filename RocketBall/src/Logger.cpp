#include "Logger.h"

#include <iostream>

void Logger::LogMessage(std::string messageText)
{
	std::cout << messageText << std::endl;
}

void Logger::LogInfo(std::string infoText)
{
	std::cout << "INFO: " << infoText << std::endl;
}

void Logger::LogWarning(std::string warningText)
{
	std::cout << "WARN: " << warningText << std::endl;
}

void Logger::LogError(std::string errorText)
{
	std::cout << "ERROR: " << errorText << std::endl;
}
