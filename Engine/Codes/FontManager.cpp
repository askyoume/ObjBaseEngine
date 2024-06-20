#include "FontManager.h"

bool Core::FontManager::Initialize()
{
	if (FAILED(InitializeDWrite()))
		return false;

	HRESULT hresult = S_OK;
	_pFont _pDefaultFont{ nullptr };

	hresult = _pDWriteFactory->CreateTextFormat(
		L"����",
		nullptr,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		34.0f,
		L"en-us",
		&_pDefaultFont
	);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create text format.", L"Error", MB_OK);
		return false;
	}
	else
	{
		_fontMap[L"DefaultFont"] = _pDefaultFont;
	}

	return true;
}

_pFont Core::FontManager::GetFont(_pwstring fontName)
{
	auto iter = _fontMap.find(fontName);
	if (iter == _fontMap.end())
	{
		MessageBoxW(nullptr, L"Failed to find font.", L"Error", MB_OK);
		return nullptr;
	}

	return iter->second;
}

HRESULT Core::FontManager::LoadFontFile(_pwstring fontFilePath, _pwstring fontName, float fontSize)
{
	HRESULT hresult = S_OK;

	IDWriteFontFile*			_pFontFile{ nullptr };
	IDWriteFontSet*				_pFontSet{ nullptr };
	IDWriteFontCollection1*		_pFontCollection{ nullptr };
	IDWriteFontFamily*			_pFontFamily{ nullptr };
	IDWriteLocalizedStrings*	_pFontFamilyNames{ nullptr };

	hresult = _pDWriteFactory->CreateFontFileReference(
		fontFilePath,
		nullptr,
		&_pFontFile
	);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create font file reference.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pFontSetBuilder->AddFontFile(_pFontFile);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to add font file.", L"Error", MB_OK);
		return hresult;
	}

	BOOL isSupported;
    DWRITE_FONT_FILE_TYPE fileType;
    UINT32 numberOfFonts;
    hresult = _pFontFile->Analyze(&isSupported, &fileType, nullptr, &numberOfFonts);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to analyze font file.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pFontSetBuilder->CreateFontSet(&_pFontSet);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create font set.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pDWriteFactory->CreateFontCollectionFromFontSet(
		_pFontSet,
		&_pFontCollection
	);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create font collection from font set.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pFontCollection->GetFontFamily(
		0,
		&_pFontFamily
	);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to get font family.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pFontFamily->GetFamilyNames(&_pFontFamilyNames);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to get family names.", L"Error", MB_OK);
		return hresult;
	}

	WCHAR familyName[MAX_PATH];
	hresult = _pFontFamilyNames->GetString(0, familyName, MAX_PATH);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to get string.", L"Error", MB_OK);
		return hresult;
	}

	_pFont _pNewFont{ nullptr };
	hresult = AddFont(familyName, fontSize, _pFontCollection, &_pNewFont);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to add font.", L"Error", MB_OK);
		return hresult;
	}
	else
	{
		_fontMap[fontName] = _pNewFont;
	}

	_pFontFile->Release();
	_pFontSet->Release();
	_pFontCollection->Release();
	_pFontFamily->Release();

	return hresult;
}

Core::FontManager* Core::FontManager::Create()
{
	static FontManager* pFontManager = new FontManager;
	if (pFontManager->Initialize())
		return pFontManager;

	return nullptr;
}

void Core::FontManager::Remove()
{
	for (auto& [key, value] : _fontMap)
	{
		SafeRelease(value);
	}

	_fontMap.clear();

	if (_pFontSetBuilder)
	{
		SafeRelease(_pFontSetBuilder);
	}
	if (_pDWriteFactory)
	{
		SafeRelease(_pDWriteFactory);
	}
}

HRESULT Core::FontManager::InitializeDWrite()
{
	HRESULT hresult = S_OK;

	hresult = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory5),
		reinterpret_cast<IUnknown**>(&_pDWriteFactory)
	);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create DWrite factory.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pDWriteFactory->CreateFontSetBuilder(&_pFontSetBuilder);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create font set builder.", L"Error", MB_OK);
		return hresult;
	}

	return hresult;
}

HRESULT Core::FontManager::AddFont(_pwstring fontName, float fontSize,IDWriteFontCollection1* pFontCollection , _pFont* ppTextFormat)
{
	HRESULT hresult = S_OK;

	hresult = _pDWriteFactory->CreateTextFormat(
		fontName,
		pFontCollection,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"en-us",
		ppTextFormat
	);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create text format.", L"Error", MB_OK);
		return hresult;
	}

	return hresult;
}
