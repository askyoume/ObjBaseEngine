#pragma once
#include "../../Engine/Headers/Core_Define.h"

namespace Client
{
	Interface IPlayerInfo
	{
		void DamageInvoker(int damage) PURE;
		int GetHP() const PURE;
		int GetMaxHP() const PURE;
		int GetGauge() const PURE;
		int GetMaxGauge() const PURE;
	};
}