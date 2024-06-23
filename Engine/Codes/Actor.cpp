#include "Actor.h"
#include "Component.h"
#include "CoreManager.h"
#include "Texture.h"
#include "BitmapComponent.h"

void Core::Actor::BeginPlay()
{
	Object::CreateObjectDirectory();

	::Core::CoreManager* pCore = ::Core::CoreManager::GetInstance();

	_bstr_t convertName = this->name;
	_pwstring tempName = convertName;

	_vecTextures.push_back(pCore->FindTexture(convertName));

}

void Core::Actor::Tick(_float deltaTime)
{
	for (auto& component : _vecComponents)
	{
		component->TickComponent(deltaTime);
	}
}

void Core::Actor::Fixed()
{

}

void Core::Actor::EndPlay()
{
}

bool Core::Actor::SetRootComponent(SceneComponent* pRootComponent)
{
	_pRootComponent = pRootComponent;

	return true;
}

void Core::Actor::AttachToActor(Actor* pParent)
{
	_pParent = pParent;
	_pRootComponent->AttachToComponent(_pParent->GetRootComponent());
}

void Core::Actor::DetachFromActor()
{
	_pRootComponent->AttachToComponent(nullptr);
	_pParent = nullptr;
}

void Core::Actor::Remove()
{
	for (auto& component : _vecComponents)
		SafeDelete(component);

	_vecComponents.clear();
}
