#pragma once
#include "RenderComponent.h"
#include "ACollision.h"

namespace Core
{
	CORECLASS()
	class BitmapComponent : public RenderComponent
	{
	protected:
		using BitmapTextures = std::vector<Texture*>;

	protected:
		explicit BitmapComponent() = default;
		virtual ~BitmapComponent() = default;

	public:
		virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

	public:
		void SetTextures(BitmapTextures* vecTextures);
		void SetTextureIndex(int index) { _currentTextureIndex = index; }
		void SetTextureRect(Texture* pTexture);
		Mathf::Rect GetTextureRect();

	public:
		void SetBitmapLocalTransform();
		void SetBitmapIndex(int index) { _currentBitmapIndex = index; }
		void SetCenterAlignment(bool isCenterAlignment) { _isCenterAlignment = isCenterAlignment; }
		bool IsCenterAlignment() { return _isCenterAlignment; }

	public:
		void SetFlip(bool isFlip) { _isFlip = isFlip; }
		bool IsFlip() { return _isFlip; }

	protected:
		virtual bool Initialize() override;
		virtual void Remove() override;

	public:
		static BitmapComponent* Create();

	protected:
		BitmapTextures*		_vecTextures{ nullptr };
		Mathf::Rect			_textureRect{};
		Mathf::Matrix3x2	_localTransform{ Matx::Identity };
		Mathf::Vector2		_localScale{ UnitVector::Zero };
		Mathf::Vector2		_localLocation{ UnitVector::Zero };
		int					_currentTextureIndex{ 0 };
		int					_currentBitmapIndex{ 0 };
		bool 				_isFlip{ false };
		bool				_isCenterAlignment{ true };
	};
}