#pragma once
#include "RenderComponent.h"

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
		virtual void Render(ID2D1RenderTarget* pRenderTarget);
		void SetTextures(BitmapTextures* vecTextures);
		void SetTextureIndex(int index) { _currentTextureIndex = index; }
		void SetTextureRect(Texture* pTexture);
		void SetBitmapLocalTransform();

	protected:
		virtual bool Initialize();
		virtual void Remove();

	public:
		static BitmapComponent* Create();

	private:
		BitmapTextures*		_vecTextures{ nullptr };
		Mathf::Rect			_textureRect{};
		Mathf::Matrix3x2	_localTransform{ Matx::Identity };
		Mathf::Vector2		_localScale{ UnitVector::Zero };
		Mathf::Vector2		_localLocation{ UnitVector::Zero };
		int					_currentTextureIndex{};
	};
}