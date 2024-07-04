#include "BitmapComponent.h"
#include "CoreManager.h"
#include "Texture.h"
#include "Actor.h"

void Core::BitmapComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (!_vecTextures) { return; }
	if (_vecTextures->empty()) { return; }
	if (!_isVisible) { return; }

	Texture* pTexture = _vecTextures->at(_currentTextureIndex);

	SetTextureRect(pTexture);

	SetBitmapLocalTransform();

	D2D1InvertMatrix(&_cameraMatrix);

	if (_isFlip)
	{
		_localTransform = D2D1::Matrix3x2F::Scale(-1, 1, 
				D2D1::Point2F(_textureRect.right * 0.5f, _textureRect.bottom * 0.5f)) * _localTransform;
	}

	Mathf::Matrix3x2 Transform = _localTransform * _WorldTransform * _cameraMatrix;

	pRenderTarget->SetTransform(Transform);

	pRenderTarget->DrawBitmap((*pTexture)[0]);

	CoreManager* _pCore = CoreManager::GetInstance();

	_pCollision->SetCollisionOffset({ _textureRect.right * 0.5f, _textureRect.bottom * 0.5f });
	//_pCollision->SetCollisionScale(_localScale);
	_pCore->GetGraphicsPackage()->_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
	float collisionOffsetX = _pCollision->GetCollisionOffset().x;
	float collisionOffsetY = _pCollision->GetCollisionOffset().y;

	//float collisionOffsetX = _WorldTransform.dx;
	//float collisionOffsetY = _WorldTransform.dy;

	Mathf::Vector2 point = { collisionOffsetX, collisionOffsetY };
	pRenderTarget->DrawLine(D2D1::Point2F(point.x - 5.0f, point.y), D2D1::Point2F(point.x + 5.0f, point.y), _pCore->GetGraphicsPackage()->_pBrush, 1.0f);
	pRenderTarget->DrawLine(D2D1::Point2F(point.x, point.y - 5.0f), D2D1::Point2F(point.x, point.y + 5.0f), _pCore->GetGraphicsPackage()->_pBrush, 1.0f);

	Mathf::Rect collisionRect = { 
		(_pCollision->GetCollisionOffset().x - _pCollision->GetCollisionSize().x * 0.5f), 
		(_pCollision->GetCollisionOffset().y - _pCollision->GetCollisionSize().y * 0.5f),
		(_pCollision->GetCollisionOffset().x + _pCollision->GetCollisionSize().x * 0.5f),
		(_pCollision->GetCollisionOffset().y + _pCollision->GetCollisionSize().y * 0.5f)
	};

	pRenderTarget->DrawRectangle(D2D1::RectF(collisionRect.left, collisionRect.top, collisionRect.right, collisionRect.bottom), _pCore->GetGraphicsPackage()->_pBrush, 1.0f);

	//pRenderTarget->SetTransform(_renderMatrix);
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

	_pCollision->SetCollisionSize({ _textureRect.right, _textureRect.bottom });

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

//Mathf::Rect Core::BitmapComponent::GetTransformedTextureRect()
//{
//	/*if (!_vecTextures) { return Mathf::Rect(); }
//	if (0 == _textureRect.right || 0 == _textureRect.bottom) 
//	{ 
//		Texture* pTexture = _vecTextures->at(_currentTextureIndex);
//	
//		SetTextureRect(pTexture); 
//	}
//
//	Mathf::Vector2 WorldLocation{};
//
//	WorldLocation.x = _MidCalculateTransform._31;
//	WorldLocation.y = _MidCalculateTransform._32;
//
//	Mathf::Rect transformedRect{
//		WorldLocation.x - _textureRect.right * 0.5f,
//		WorldLocation.y - _textureRect.bottom * 0.5f,
//		WorldLocation.x + _textureRect.right * 0.5f,
//		WorldLocation.y + _textureRect.bottom * 0.5f
//	};
//
//	std::cout << "Transformed Rect : " << transformedRect.left << " " << transformedRect.top << " " << transformedRect.right << " " << transformedRect.bottom << std::endl;
//
//	return transformedRect;*/
//}

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

	_pCollision = ACollision::Create();

    return true;
}

void Core::BitmapComponent::Remove()
{
	RemoveRenderQueueInLayer();

	SafeRelease(_pCollision);

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
