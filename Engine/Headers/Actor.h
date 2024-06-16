#pragma once
#include "Core_Define.h"
#include "Object.h"
#include "Mathf.h"

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
		//virtual void Render(ID2D1RenderTarget* pRenderTarget);
		virtual void EndPlay();

	public:
		template <typename T>
		T* AddComponent(_pstring name)
		{
			bool isBaseComponent = std::is_base_of<Component, T>::value;
			static_assert(std::is_base_of<Component, T>::value, "T must derive form Component");

			T* pComponent = T::Create();
			pComponent->SetOwner(this);
			pComponent->SetName(name);
			//이게 맞니? ㅋㅋㅋㅋ
			bool isSceneComponent = std::is_base_of<SceneComponent, T>::value;
			bool isRootComponent = (nullptr == _pRootComponent);
			if (isSceneComponent && !isRootComponent)
			{
				SceneComponent* pSceneComponent = dynamic_cast<SceneComponent*>(pComponent);
				pSceneComponent->AttachToComponent(_pRootComponent);
			}

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

		bool SetRootComponent(SceneComponent* pRootComponent);
		SceneComponent* GetRootComponent() const { return _pRootComponent; }

		void SetLayerIndex(int layerIndex) { _layerIndex = layerIndex; }
		int GetLayerIndex() const { return _layerIndex; }

	protected:
		virtual void Remove() override PURE;

	protected:
		SceneComponent*			_pRootComponent{ nullptr };
		Actor*					_pParent{ nullptr };
		World*					_pOwnerWorld{ nullptr };
		int						_layerIndex{ 0 };
		std::vector<Component*> _vecComponents;
		std::vector<Texture*>	_vecTextures;
	};
}