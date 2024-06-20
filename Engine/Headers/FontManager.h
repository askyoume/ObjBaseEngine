#pragma once
#include "Core_Define.h"

namespace Core
{
	class FontManager : public Core
	{
	private:
		explicit FontManager() DEFAULT;
		virtual ~FontManager() DEFAULT;

	public:
		bool Initialize();
		_pFont GetFont(_pwstring fontName);
		HRESULT LoadFontFile(_pwstring fontFilePath, _pwstring fontName, float fontSize);

	public:
		static FontManager* Create();
		void Remove() override;

	private:
		HRESULT InitializeDWrite();
		HRESULT AddFont(_pwstring fontName, float fontSize,IDWriteFontCollection1* pFontCollection, _pFont* ppTextFormat);

	private:
		IDWriteFactory5*		_pDWriteFactory{ nullptr };
		IDWriteFontSetBuilder1*	_pFontSetBuilder{ nullptr };
		std::unordered_map<_pwstring, _pFont> _fontMap;
	};
}