#pragma once

#include <format>
#include <string>
#include <utility>

enum class LogLevel {
	Debug,
	Info,
	Warning,
	Error
};

class Logger {
public:
	static Logger instance();

	// Logger(const Logger&) = delete;
	// Logger& operator=(const Logger&) = delete;

	void log(LogLevel level, const std::string& message) const;
	template <typename... Args>
	void log(LogLevel level, std::format_string<Args...> format, Args&&... args) const {
		log(level, std::format(format, std::forward<Args>(args)...));
	}

	void debug(const std::string& message) const;
	template <typename... Args>
	void debug(std::format_string<Args...> format, Args&&... args) const {
		log(LogLevel::Debug, format, std::forward<Args>(args)...);
	}

	void info(const std::string& message) const;
	template <typename... Args>
	void info(std::format_string<Args...> format, Args&&... args) const {
		log(LogLevel::Info, format, std::forward<Args>(args)...);
	}

	void warning(const std::string& message) const;
	template <typename... Args>
	void warning(std::format_string<Args...> format, Args&&... args) const {
		log(LogLevel::Warning, format, std::forward<Args>(args)...);
	}

	void error(const std::string& message) const;
	template <typename... Args>
	void error(std::format_string<Args...> format, Args&&... args) const {
		log(LogLevel::Error, format, std::forward<Args>(args)...);
	}

private:
	Logger() = default;
};