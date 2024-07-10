#pragma once
#include "../../Engine/Headers/State.h"

namespace Client
{
	class Aoko;
	class Idle : public Core::State
	{
	protected:
		explicit Idle() DEFAULT;
		virtual ~Idle() DEFAULT;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static Idle* Create();

	private:
		Aoko* pAoko{ nullptr };
	};
}