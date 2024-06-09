#pragma once
#include "Object.h"

namespace Core
{
	CORECLASS()
	class Component abstract : public Object
	{
	protected:
		explicit Component() DEFAULT;
		virtual ~Component() DEFAULT;

	public:
		virtual void BeginPlay() PURE;
		virtual void TickComponent(_float deltaTime) PURE;
		virtual void EndPlay() PURE;

	public:
		void SetDisable() { _isDisable = true; }

	public:
		virtual void SetOwner(Actor* owner) { _owner = owner; }

	protected:
		virtual bool Initialize() PURE;
		virtual void Remove() override PURE;

	protected:
		Actor* _owner = nullptr;
		bool _isDisable = false;
	};
}
