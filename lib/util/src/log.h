#pragma once
#include "num.h"

enum Level {
	Trace,
	Debug,
	Info,
	Warn,
	Error,
};

void log(Level level, const char* file, u16 line, const char* msg);
void die(const char* file, u16 line, const char* msg);

#define LOG(level, msg) log(level, __FILE__, __LINE__, msg);
#define LOG_TRACE(msg) LOG(Level::Trace, msg);
#define LOG_DEBUG(msg) LOG(Level::Debug, msg);
#define LOG_INFO(msg) LOG(Level::Info, msg);
#define LOG_WARN(msg) LOG(Level::Warn, msg);
#define LOG_ERROR(msg) LOG(Level::Error, msg);
#define DIE(msg) die(__FILE__, __LINE__, msg);
