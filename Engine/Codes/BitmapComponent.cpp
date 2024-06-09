#include "BitmapComponent.h"
#include "Texture.h"

void Core::BitmapComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (_isVisible == false)
	{
		return;
	}

	if (_vecTextures == nullptr)
	{
		return;
	}

	if (_vecTextures->empty())
	{
		return;
	}

	if (_currentTextureIndex >= _vecTextures->size())
	{
		_currentTextureIndex = 0;
	}

	Matrix3x2 Transform = _renderMatrix * _WorldTransform;

	pRenderTarget->SetTransform(Transform);

	Texture* pTexture = _vecTextures->at(_currentTextureIndex);
	pRenderTarget->DrawBitmap((*pTexture)[0], D2D1::RectF(0, 0, 1000, 590));

	//1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, _transform.GetRect());
}

bool Core::BitmapComponent::Initialize()
{
    return true;
}

void Core::BitmapComponent::Remove()
{
	_vecTextures = nullptr;
}

Core::BitmapComponent* Core::BitmapComponent::Create(BitmapTextures* vecTextures)
{
	BitmapComponent* pInstance = new BitmapComponent;
	pInstance->_vecTextures = vecTextures;
	if (pInstance->Initialize())
	{
		return pInstance;
	}

	return nullptr;
}
