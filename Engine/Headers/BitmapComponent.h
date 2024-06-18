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
		int					_currentTextureIndex{ 0 };
		Mathf::Rect			_rect{ 0, 0, 0, 0 };
		Mathf::Matrix3x2	_LocalTransform{ Matx::Identity };
		Mathf::Vector2		_LocalScale{ UnitVector::Zero };
		Mathf::Vector2		_LocalLocation{ UnitVector::Zero };
	};
}