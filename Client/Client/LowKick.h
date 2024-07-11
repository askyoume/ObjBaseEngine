#pragma once
#include "../../Engine/Headers/State.h"

namespace Client
{
	class Aoko;
	class LowKick : public Core::State
	{
	protected:
		explicit LowKick() DEFAULT;
		virtual ~LowKick() DEFAULT;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static LowKick* Create();

	private:
		Aoko* pAoko{ nullptr };
		bool isLowKick{ false };
		float _elapsedTime{ 0.f };
		float _lowKickSpeed{ 5.f };
	};
}