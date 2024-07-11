#pragma once
#include "Core_Define.h"
#include "Component.h"

namespace Core
{
	CORECLASS()
	class StateComponent : public Component
	{
	protected:
		explicit StateComponent() DEFAULT;
		virtual ~StateComponent() DEFAULT;

	public:
		virtual bool Initialize() override;
		virtual void BeginPlay() override;
		virtual void TickComponent(_float deltaTime) override;
		virtual void EndPlay() override;
		virtual void Remove() override;

	public:
		template <typename T>
		void AddContainer()
		{
			StateContainer* newContainer = T::Create();
			newContainer->SetOwner(this);
			newContainer->ContainStep();
			_pContainer = newContainer;
		}

	public:
		static StateComponent* Create() { return new StateComponent; }

	public:
		_pstring GetCurrentStateName() const;

	protected:
		StateContainer* _pContainer{ nullptr };
	};


}