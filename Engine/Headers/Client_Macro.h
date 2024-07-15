#pragma once

#define DENY_COPY(ClassName)						\
	ClassName(const ClassName&) = delete;			\
	ClassName(ClassName&&) = delete;				\
	ClassName& operator=(ClassName&&) = delete;		\
	ClassName& operator=(const ClassName&) = delete;

#define CLIENTCLASS()                 \
    class System;

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif