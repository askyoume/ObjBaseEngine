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

	Mathf::Matrix3x2 flipMatrix = Matx::Identity;
	if (_isFlip)
	{
		flipMatrix = D2D1::Matrix3x2F::Scale(-1, 1, 
				D2D1::Point2F(_textureRect.right * 0.5f, _textureRect.bottom * 0.5f)) * _localTransform;
	}
	else
	{
		flipMatrix = _localTransform;
	}

	Mathf::Matrix3x2 Transform = _localTransform * _WorldTransform * _cameraMatrix;

	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawBitmap((*pTexture)[0]);
	//TODO: Debug Code
	CoreManager* _pCore = CoreManager::GetInstance();

	Mathf::Matrix3x2 CollisionTransform = _localTransform * _WorldTransform * _cameraMatrix;

	_pCollision->SetCollisionOffset(
		{ CollisionTransform.dx + (_textureRect.right * 0.5f) * _RelativeScale.x,
		CollisionTransform.dy + (_textureRect.bottom * 0.5f) * _RelativeScale.y }
	);

	float collisionOffsetX = _pCollision->GetCollisionOffset().x;
	float collisionOffsetY = _pCollision->GetCollisionOffset().y;

	ID2D1SolidColorBrush* m_pBrush = _pCore->GetGraphicsPackage()->_pBrush;
	m_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));

	//pRenderTarget->SetTransform(Matx::Identity);

	//m_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	//pRenderTarget->DrawLine(D2D1::Point2F(collisionOffsetX - 5.0f, collisionOffsetY), D2D1::Point2F(collisionOffsetX + 5.0f, collisionOffsetY), m_pBrush, 1.0f);
	//pRenderTarget->DrawLine(D2D1::Point2F(collisionOffsetX, collisionOffsetY - 5.0f), D2D1::Point2F(collisionOffsetX, collisionOffsetY + 5.0f), m_pBrush, 1.0f);
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

	_pCollision->SetCollisionSize({ _textureRect.right * _RelativeScale.x, _textureRect.bottom * _RelativeScale.y });

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

void Core::BitmapComponent::SetBitmapLocalTransform()
{
	_localLocation.x = _textureRect.right * 0.5f;
	_localLocation.y = _textureRect.bottom * 0.5f;

	_localTransform = D2D1::Matrix3x2F::Translation(-_localLocation.x, -_localLocation.y);
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
