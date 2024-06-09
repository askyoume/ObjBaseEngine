#pragma once
#include "Core_Define.h"
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
		virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

	protected:
		virtual bool Initialize() override;
		virtual void Remove() override;

	public:
		static BitmapComponent* Create(BitmapTextures* vecTextures);

	private:
		BitmapTextures* _vecTextures{ nullptr };
		int _currentTextureIndex{ 0 };
	};
}