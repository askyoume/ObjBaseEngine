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

	protected:
		virtual bool Initialize();
		virtual void Remove();

	public:
		static BitmapComponent* Create();

	private:
		BitmapTextures* _vecTextures{ nullptr };
		int _currentTextureIndex{ 0 };
		Mathf::Rect _rect{ 0, 0, 0, 0 };
	};
}