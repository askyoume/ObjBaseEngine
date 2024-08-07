#pragma once
#include "Object.h"

namespace Core
{
	CORECLASS()
	class Component abstract : public Object
	{
	protected:
		explicit Component() = default;
		virtual ~Component() = default;

	public:
		virtual void BeginPlay() PURE;
		virtual void TickComponent(_float deltaSeconds) PURE;
		virtual void EndPlay() PURE;

	public:
		void SetDisable() { _isDisable = true; }

	public:
		virtual void SetOwner(Actor* owner) { _owner = owner; }
		Actor* GetOwner() const { return _owner; }

	protected:
		virtual bool Initialize() PURE;
		virtual void Remove() override PURE;

	protected:
		Actor* _owner = nullptr;
		bool _isDisable = false;
	};
}
