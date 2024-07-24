#pragma once
#include "RenderComponent.h"
#include "Mathf.h"

namespace Core
{
	class TextRenderComponent final : public RenderComponent
	{
	protected:
		explicit TextRenderComponent() = default;
		virtual ~TextRenderComponent() = default;

	public:
		virtual void TickComponent(_float deltaSeconds) override;
		virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

	public:
		void SetText(const _bstring& text);
		void SetFont(_pwstring fontName);
		void SetSize(const Mathf::Vector2& size);
		void SetColor(const D2D1_COLOR_F& color);
		_pFont GetFont() const { return _font; }

	public:
		static TextRenderComponent* Create();

	private:
		virtual bool Initialize() override;
		virtual void Remove() override;

	private:
		ID2D1SolidColorBrush*	_pBrush{ nullptr };
		D2D1_COLOR_F			_color{ D2D1::ColorF::White };
		D2D1_COLOR_F			_systemColor{ D2D1::ColorF::White };
		Mathf::Rect				_textRect{};

	private:
		_bstring _text{};
		_pFont	 _font{ nullptr };
	};
}