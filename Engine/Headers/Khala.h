#pragma once
#include <tuple>
#include "KhalaBase.h"

template <typename... Args>
struct Khala : public KhalaBase
{
	std::tuple<Args...> params;

	Khala(Args... args) : params(std::make_tuple(args...)) {}
};