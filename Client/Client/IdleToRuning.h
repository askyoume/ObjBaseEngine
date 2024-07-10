#pragma once
#include "../../Engine/Headers/StateTransition.h"

namespace Client
{
	class Aoko;
	class IdleToRuning : public Core::StateTransition
	{
	protected:
		explicit IdleToRuning() DEFAULT;
		virtual ~IdleToRuning() DEFAULT;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static IdleToRuning* Create();

	private:
		Aoko* pAoko{ nullptr };
	};
}