#pragma once

#define PURE = 0

#define DEFAULT = default

#define DENY_COPY(ClassName)						\
	ClassName(const ClassName&) = delete;			\
	ClassName(ClassName&&) = delete;				\
	ClassName& operator=(ClassName&&) = delete;		\
	ClassName& operator=(const ClassName&) = delete;

#define CLIENTCLASS()                 \
    class System;