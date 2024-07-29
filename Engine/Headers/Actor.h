#pragma once
#include "Core_Define.h"
#include "Object.h"
#include "Mathf.h"
#include "IColliderReceiver.h"

namespace Core
{
	CORECLASS()
	class Actor abstract : public Object, public IColliderReceiver
	{
	protected:
		explicit Actor() = default;
		virtual ~Actor() = default;

	public:
		virtual void BeginPlay();
		virtual void Tick(_float deltaSeconds);
		virtual void Fixed();
		virtual void EndPlay();
		virtual void NotifyActorBlock(CollisionPackage Components) override {};
		virtual void NotifyActorBeginOverlap(CollisionPackage Components) override {};
		virtual void NotifyActorEndOverlap(CollisionPackage Components) override {};
		virtual void ReviveInitialize() {};

	public:
		template <typename T>
		T* AddComponent(_pstring name)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must derive form Component");

			T* pComponent = T::Create();
			pComponent->SetOwner(this);
			pComponent->SetName(name);

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

	public:
		bool operator==(_pstring name) const { return !strcmp(this->name, name); }
		bool operator!=(_pstring name) const { return strcmp(this->name, name); }

	public:
		bool SetRootComponent(SceneComponent* pRootComponent);
		SceneComponent* GetRootComponent() const { return _pRootComponent; }
		void SetLayerIndex(int layerIndex) { _layerIndex = layerIndex; }
		int GetLayerIndex() const { return _layerIndex; }
		void AttachToActor(Actor* pParent);
		void DetachFromActor();
		Actor* GetParent() const { return _pParent; }
		void SetWorld(World* world) { _pOwnerWorld = world; }
		World* GetWorld() const { return _pOwnerWorld; }
		void AddTexture(Texture* pTexture) { _vecTextures.push_back(pTexture); }
		size_t GetTextureSize() const { return _vecTextures.size(); }
		Texture* GetFrame(int index) const { return _vecTextures[index]; }

	protected:
		void Remove() override;

	protected:
		SceneComponent*			_pRootComponent{ nullptr };
		Actor*					_pParent{ nullptr };
		World*					_pOwnerWorld{ nullptr };
		int						_layerIndex{ 0 };
		std::vector<Actor*>		_vecChildren;
		std::vector<Component*> _vecComponents;
		std::vector<Texture*>	_vecTextures;
	};
}