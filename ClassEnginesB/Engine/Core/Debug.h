#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <fstream>

enum class messageType : unsigned short {
	TYPE_NONE,
	TYPE_FATAL_ERROR,
	TYPE_ERROR,
	TYPE_WARNING,
	TYPE_TRACE,
	TYPE_INFO
};

class Debug {
public:
	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;

	static void debugInit();
	static void setSeverity(messageType type_);
	static void info(const std::string& message_, const std::string& fileName_, const int line_);
	static void trace(const std::string& message_, const std::string& fileName_, const int line_);
	static void warning(const std::string& message_, const std::string& fileName_, const int line_);
	static void error(const std::string& message_, const std::string& fileName_, const int line_);
	static void fatalError(const std::string& message_, const std::string& fileName_, const int line_);

private:
	static void log(const messageType type_, const std::string& message_, const std::string& fileName_, const int line_);
	static messageType currentSev;
	static std::string outputName;


};

#endif //!DEBUG_H