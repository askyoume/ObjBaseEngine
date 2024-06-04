#include "Texture.h"

ID2D1Bitmap* Core::Texture::LoadTexture(LPCWSTR filePath)
{
	BitmapPtrPackage pBitmapPtrPackage;

	HRESULT hresult = _pPackage->_pWICFactory->CreateDecoderFromFilename(
		filePath, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pBitmapPtrPackage._pDecoder);
	if(SUCCEEDED(hresult))
	{
		hresult = pBitmapPtrPackage._pDecoder->GetFrame(0, &pBitmapPtrPackage._pFrame);
	}

	if(SUCCEEDED(hresult))
	{
		hresult = _pPackage->_pWICFactory->CreateFormatConverter(&pBitmapPtrPackage._pConverter);
	}

	if(SUCCEEDED(hresult))
	{
		hresult = pBitmapPtrPackage._pConverter->Initialize(
			pBitmapPtrPackage._pFrame, GUID_WICPixelFormat32bppPBGRA, 
			WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeMedianCut);
	}

	if(SUCCEEDED(hresult))
	{
		hresult = _pPackage->_pD2DRenderTarget->CreateBitmapFromWicBitmap(
			pBitmapPtrPackage._pConverter, nullptr, &pBitmapPtrPackage._pBitmap);
	}

	if(pBitmapPtrPackage._pDecoder)
	{
		pBitmapPtrPackage._pDecoder->Release();
		pBitmapPtrPackage._pDecoder = nullptr;
	}

	if(pBitmapPtrPackage._pConverter)
	{
		pBitmapPtrPackage._pConverter->Release();
		pBitmapPtrPackage._pConverter = nullptr;
	}

	if(pBitmapPtrPackage._pFrame)
	{
		pBitmapPtrPackage._pFrame->Release();
		pBitmapPtrPackage._pFrame = nullptr;
	}

	if(SUCCEEDED(hresult))
	{
		_vecOriginBitmaps.push_back(pBitmapPtrPackage._pBitmap);
		return pBitmapPtrPackage._pBitmap;
	}

	return nullptr;
}

bool Core::Texture::Initialize(GraphicsPtrPackage* package)
{
	_pPackage = package;

	return true;
}

void Core::Texture::Remove()
{
	for (auto& Bitmap : _vecOriginBitmaps)
		delete Bitmap;

	_vecOriginBitmaps.clear();
	_vecOriginBitmaps.shrink_to_fit();
}

Core::Texture* Core::Texture::Create(GraphicsPtrPackage* package)
{
	Texture* pInstance = new Texture;
	if (pInstance->Initialize(package))
	{
		return pInstance;
	}

	SafeDelete(pInstance);
	return nullptr;
}
