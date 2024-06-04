#pragma once
#include "Core_Define.h"
#include "IInputReceiver.h"
#include "Object.h"

namespace Core
{
	CORECLASS()
	class Actor abstract : public Object
	{
	protected:
		explicit Actor() DEFAULT;
		virtual ~Actor() DEFAULT;

	public:
		virtual void BeginPlay();
		virtual void Tick(_float deltaTime);
		virtual void Fixed();
		virtual void Render(ID2D1RenderTarget* pRenderTarget);
		virtual void EndPlay();

	public:
		template <typename T>
		T* CreateComponent(_pstring name)
		{
			bool isBaseComponent = std::is_base_of<Component, T>::value;
			static_assert(std::is_base_of<Component, T>::value, "T must derive form Component");
			assert(isBaseComponent);

			T* pComponent = T::Create();
			pComponent->SetOwner(this);
			pComponent->SetName(name);
			_vecComponents.push_back(pComponent);
			return pComponent;
		}

		template <typename T>
		T* GetComponent(_pstring name)
		{
			for (auto& component : _vecComponents)
			{
				if (!strcmp(component->GetName(),name))
					return static_cast<T*>(component);
			}
			return nullptr;
		}

	protected:
		virtual void Remove() override PURE;

	protected:
		Actor*					_pParent{ nullptr };
		World*					_pOwnerWorld{ nullptr };
		int						_layerIndex{ 0 };
		std::vector<Component*> _vecComponents;
	};
}