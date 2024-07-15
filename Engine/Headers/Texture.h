#pragma once
#include "Core_Define.h"

namespace Core
{
	class Texture : public Core
	{
	private:
		explicit Texture() = default;
		virtual ~Texture() = default;

	public:
		ID2D1Bitmap* operator[](const int index) const { return _vecOriginBitmaps[index]; }
		ID2D1Bitmap* GetImage(const int index, bool isFlip) const { return _vecOriginBitmaps[index]; }
		int GetImageCount() const { return (int)_vecOriginBitmaps.size(); }

	public:
		ID2D1Bitmap* LoadTexture(LPCWSTR filePath);

	private:
		bool Initialize(GraphicsPtrPackage* package);
		void Remove() override;

	public:
		static Texture* Create(GraphicsPtrPackage* package);

	private:
		std::vector<ID2D1Bitmap*> _vecOriginBitmaps;
		GraphicsPtrPackage* _pPackage{ nullptr };
		BitmapPtrPackage pBitmapPtrPackage;

	};
}