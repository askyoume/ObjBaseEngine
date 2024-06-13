#include "BitmapComponent.h"
#include "Texture.h"
#include "Actor.h"

void Core::BitmapComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (_isVisible == false) { return; }
	if (_vecTextures == nullptr) { return; }
	if (_vecTextures->empty()) { return; }

	if (_currentTextureIndex >= _vecTextures->size())
	{
		_currentTextureIndex = 0;
	}
	Texture* pTexture = _vecTextures->at(_currentTextureIndex);

	SetTextureRect(pTexture);

	_LocalLocation.x = _rect.right / 2;
	_LocalLocation.y = _rect.bottom / 2;

	Mathf::Matrix3x2 Transform = _renderMatrix * _WorldTransform;

	pRenderTarget->SetTransform(Transform);
		
	pRenderTarget->DrawBitmap((*pTexture)[0]);

	pRenderTarget->SetTransform(_renderMatrix);

}

void Core::BitmapComponent::SetTextureRect(Texture* pTexture)
{
	D2D1_SIZE_F _size = (*pTexture)[0]->GetSize();

	_rect = D2D1::RectF(0, 0, _size.width, _size.height);
}

bool Core::BitmapComponent::Initialize()
{
	if (!RenderComponent::Initialize())
	{
		return false;
	}

    return true;
}

void Core::BitmapComponent::Remove()
{
	_vecTextures = nullptr;
}

Core::BitmapComponent* Core::BitmapComponent::Create()
{
	BitmapComponent* pInstance = new BitmapComponent;
	if (pInstance->Initialize())
	{
		return pInstance;
	}

	return nullptr;
}