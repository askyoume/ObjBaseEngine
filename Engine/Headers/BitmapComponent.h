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
		explicit BitmapComponent() DEFAULT;
		virtual ~BitmapComponent() DEFAULT;

	public:
		virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
		void SetTextures(BitmapTextures* vecTextures);
		void SetTextureIndex(int index) { _currentTextureIndex = index; }
		void SetTextureRect(Texture* pTexture);
		Mathf::Rect GetTextureRect();
		//Mathf::Rect GetTransformedTextureRect();
		void SetBitmapLocalTransform();
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
		int					_currentTextureIndex{};
		bool 				_isFlip{ false };
	};
}