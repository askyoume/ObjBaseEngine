#pragma once
#include "../../Engine/Headers/State.h"

namespace Client
{
	class Aoko;
	class Runing : public Core::State
	{
	protected:
		explicit Runing() DEFAULT;
		virtual ~Runing() DEFAULT;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static Runing* Create();

	private:
		Aoko* pAoko{ nullptr };
	};
}