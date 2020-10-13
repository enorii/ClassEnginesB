#include "Debug.h"

messageType Debug::currentSev = messageType::TYPE_NONE;
std::string Debug::outputName = "";

void Debug::debugInit() {
	outputName = "GameEngineLog.txt";
	std::ofstream out;
	out.open(outputName.c_str(), std::ios::out);
	out.close();
	currentSev = messageType::TYPE_FATAL_ERROR;
}

void Debug::setSeverity(messageType type_) {
	currentSev = type_;
}

void Debug::info(const std::string& message_, const std::string& fileName_, const int line_) {
	log(messageType::TYPE_INFO, "[INFO]" + message_, fileName_, line_);
}

void Debug::trace(const std::string& message_, const std::string& fileName_, const int line_) {
	log(messageType::TYPE_TRACE, "[TRACE]" + message_, fileName_, line_);
}

void Debug::warning(const std::string& message_, const std::string& fileName_, const int line_) {
	log(messageType::TYPE_WARNING, "[WARNING]" + message_, fileName_, line_);
}

void Debug::error(const std::string& message_, const std::string& fileName_, const int line_) {
	log(messageType::TYPE_ERROR, "[ERROR]" + message_, fileName_, line_);
}

void Debug::fatalError(const std::string& message_, const std::string& fileName_, const int line_) {
	log(messageType::TYPE_FATAL_ERROR, "[FATAL ERROR]" + message_, fileName_, line_);
}

void Debug::log(const messageType type_, const std::string& message_, const std::string& fileName_, const int line_) {
	if (type_ <= currentSev && currentSev > messageType::TYPE_NONE) {
		std::ofstream out;
		out.open(outputName.c_str(), std::ios::app | std::ios::out);
		out << message_ << " in: " << fileName_ << " on line: " << line_ << std::endl;
		out.flush();
		out.close();
	}
}