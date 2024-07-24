#include "CoreManager.h"
#include "TextRenderComponent.h"

void Core::TextRenderComponent::TickComponent(_float deltaSeconds)
{
	SceneComponent::TickComponent(deltaSeconds);
}

void Core::TextRenderComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	Mathf::Matrix3x2 Transform = _WorldTransform * _cameraMatrix;
	pRenderTarget->SetTransform(Transform);

	_pBrush->SetColor(_color);
	pRenderTarget->DrawTextW(_text, _text.length(), _font, _textRect, _pBrush);
	_pBrush->SetColor(_systemColor);
}

void Core::TextRenderComponent::SetText(const _bstring& text)
{
	_text = text;
}

void Core::TextRenderComponent::SetFont(_pwstring fontName)
{
	_font = CoreManager::GetInstance()->GetFont(fontName);
}

void Core::TextRenderComponent::SetSize(const Mathf::Vector2& size)
{
	Mathf::Vector2 rectHalfSize = size * 0.5f;
	Mathf::Vector2 position = GetWorldLocation();

	_textRect.left	 = -rectHalfSize.x;
	_textRect.top	 = -rectHalfSize.y;
	_textRect.right  =  rectHalfSize.x;
	_textRect.bottom =  rectHalfSize.y;
}

void Core::TextRenderComponent::SetColor(const D2D1_COLOR_F& color)
{
	_color = color;
}

bool Core::TextRenderComponent::Initialize()
{
	CoreManager* _pCore = CoreManager::GetInstance();
	_pBrush = _pCore->GetGraphicsPackage()->_pBrush;
	_systemColor = _pBrush->GetColor();

	return true;
}

void Core::TextRenderComponent::Remove()
{

}

Core::TextRenderComponent* Core::TextRenderComponent::Create()
{
	TextRenderComponent* pInstance = new TextRenderComponent();
	if (pInstance->Initialize())
	{
		return pInstance;
	}

	return nullptr;
}