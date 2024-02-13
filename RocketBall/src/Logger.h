#pragma once

#include <string>

namespace Logger
{
	extern void LogMessage(std::string messageText);
	extern void LogInfo(std::string infoText);
	extern void LogWarning(std::string warningText);
	extern void LogError(std::string errorText);
};