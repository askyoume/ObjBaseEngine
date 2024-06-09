#include "Actor.h"
#include "Component.h"
#include "CoreManager.h"
#include "Texture.h"

void Core::Actor::BeginPlay()
{
	Object::CreateObjectDirectory();
		
	::Core::CoreManager* pCore = ::Core::CoreManager::GetInstance();

	_bstr_t convertName = this->name;
	_pwstring tempName = convertName;

	_vecTextures.push_back(pCore->FindTexture(L"TestActor"));

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

void Core::Actor::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->DrawBitmap((*_vecTextures[0])[0], D2D1::RectF(0, 0, 1000, 590));
}

void Core::Actor::EndPlay()
{
}
