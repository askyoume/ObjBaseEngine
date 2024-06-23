#include "BitmapComponent.h"
#include "Texture.h"
#include "Actor.h"

void Core::BitmapComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (_isVisible == false) { return; }
	if (_vecTextures == nullptr) { return; }
	if (_vecTextures->empty()) { return; }

	Texture* pTexture = _vecTextures->at(_currentTextureIndex);

	SetTextureRect(pTexture);

	SetBitmapLocalTransform();

	D2D1InvertMatrix(&_cameraMatrix);

	Mathf::Matrix3x2 Transform = _localTransform * _WorldTransform * _cameraMatrix;

	pRenderTarget->SetTransform(Transform);
		
	pRenderTarget->DrawBitmap((*pTexture)[0]);

	pRenderTarget->SetTransform(_renderMatrix);
}

void Core::BitmapComponent::SetTextures(BitmapTextures* vecTextures)
{
	_vecTextures = vecTextures;

	AddRenderQueueInLayer();
}

void Core::BitmapComponent::SetTextureRect(Texture* pTexture)
{
	D2D1_SIZE_F _size = (*pTexture)[0]->GetSize();

	_textureRect = D2D1::RectF(0, 0, _size.width, _size.height);
}

Mathf::Rect Core::BitmapComponent::GetTextureRect()
{
	if (!_vecTextures) { return Mathf::Rect(); }
	if (0 == _textureRect.right || 0 == _textureRect.bottom) 
	{ 
		Texture* pTexture = _vecTextures->at(_currentTextureIndex);
		SetTextureRect(pTexture); 
	}

	return _textureRect;
}

Mathf::Rect Core::BitmapComponent::GetTransformedTextureRect()
{
	if (!_vecTextures) { return Mathf::Rect(); }
	if (0 == _textureRect.right || 0 == _textureRect.bottom) 
	{ 
		Texture* pTexture = _vecTextures->at(_currentTextureIndex);
	
		SetTextureRect(pTexture); 
	}

	Mathf::Vector2 WorldLocation{};

	WorldLocation.x = _MidCalculateTransform._31;
	WorldLocation.y = _MidCalculateTransform._32;

	Mathf::Rect transformedRect{
		WorldLocation.x - _textureRect.right * 0.5f,
		WorldLocation.y - _textureRect.bottom * 0.5f,
		WorldLocation.x + _textureRect.right * 0.5f,
		WorldLocation.y + _textureRect.bottom * 0.5f
	};

	std::cout << "Transformed Rect : " << transformedRect.left << " " << transformedRect.top << " " << transformedRect.right << " " << transformedRect.bottom << std::endl;

	return transformedRect;
}

void Core::BitmapComponent::SetBitmapLocalTransform()
{
	_localLocation.x = _textureRect.right * 0.5f;
	_localLocation.y = _textureRect.bottom * 0.5f;

	_localTransform = D2D1::Matrix3x2F::Translation(_localLocation.x, _localLocation.y);

	D2D1InvertMatrix(&_localTransform);
}

bool Core::BitmapComponent::Initialize()
{
	if (!RenderComponent::Initialize())	{ return false; }

    return true;
}

void Core::BitmapComponent::Remove()
{
	RemoveRenderQueueInLayer();

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
