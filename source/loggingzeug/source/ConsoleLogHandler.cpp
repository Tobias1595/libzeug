#include <loggingzeug/ConsoleLogHandler.h>

#include <iostream>

namespace loggingzeug
{

void ConsoleLogHandler::handle(const LogMessage& message)
{
    if (LogMessage::Info > message.level())
	    std::cerr << levelString(message.level()) << message.message() << std::endl;
    else
        std::cout << levelString(message.level()) << message.message() << std::endl;
}

std::string ConsoleLogHandler::levelString(LogMessage::Level level)
{
	switch (level)
	{
	case LogMessage::Fatal:
		return "#fatal: ";
	case LogMessage::Critical:
		return "#critical: ";
	case LogMessage::Warning:
		return "#warning: ";
	default:
		return "";
	}
}

} // namespace loggingzeug
