#ifndef EXCEPTION_H__
#define EXCEPTION_H__

#include <stdio.h>
#include <stdarg.h>
#include <exception>

class exceptionf: public std::exception {
	char buf[512];
public:
	exceptionf(const char *fmt, ...) {
		va_list ap;
		va_start(ap, fmt);
		vsnprintf(buf, sizeof(buf), fmt, ap);
		va_end(ap);
	}

	const char *what() {
		return buf;
	}
};

#endif /* EXCEPTION_H__ */