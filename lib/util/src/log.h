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
#define TRACE(msg) LOG(Level::Trace, msg);
#define DEBUG(msg) LOG(Level::Debug, msg);
#define INFO(msg) LOG(Level::Info, msg);
#define WARN(msg) LOG(Level::Warn, msg);
#define ERROR(msg) LOG(Level::Error, msg);
#define DIE(msg) die(__FILE__, __LINE__, msg);
