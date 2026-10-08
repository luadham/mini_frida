#include "Logger.hpp"

#include <iostream>

namespace {
const char* level_name(LogLevel level) {
	switch (level) {
	case LogLevel::Debug:
		return "DEBUG";
	case LogLevel::Info:
		return "INFO";
	case LogLevel::Warning:
		return "WARNING";
	case LogLevel::Error:
		return "ERROR";
	}
	return "UNKNOWN";
}

const char* level_color(LogLevel level) {
	switch (level) {
	case LogLevel::Debug:
		return "\033[36m";
	case LogLevel::Info:
		return "\033[32m";
	case LogLevel::Warning:
		return "\033[33m";
	case LogLevel::Error:
		return "\033[31m";
	}
	return "\033[0m";
}
}

Logger Logger::instance() {
	static Logger logger;
	return logger;
}

void Logger::log(LogLevel level, const std::string& message) const {
	std::ostream& output = level == LogLevel::Error ? std::cerr : std::clog;
	output << level_color(level) << '[' << level_name(level) << "]\033[0m "
		   << message << '\n';
}

void Logger::debug(const std::string& message) const {
	log(LogLevel::Debug, message);
}

void Logger::info(const std::string& message) const {
	log(LogLevel::Info, message);
}

void Logger::warning(const std::string& message) const {
	log(LogLevel::Warning, message);
}

void Logger::error(const std::string& message) const {
	log(LogLevel::Error, message);
}
