#include "log.h"
#include <cstdio>
#include <stdlib.h>

void log(Level level, const char* file, u16 line, const char* msg) {
	const char* levelWord;
	switch (level) {
		case Level::Trace:
			levelWord = "TRACE";
			break;
		case Level::Debug:
			levelWord = "DEBUG";
			break;
		case Level::Info:
			levelWord = "INFO";
			break;
		case Level::Warn:
			levelWord = "WARN";
			break;
		case Level::Error:
			levelWord = "ERROR";
			break;
	}

	printf("[%s] (%s:%u) %s\n", levelWord, file, line, msg);
}

void die(const char* file, u16 line, const char* msg) {
	log(Level::Error, file, line, msg);
	exit(1);
}
