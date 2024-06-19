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
		HRESULT Initialize();
		_pFont GetFont(_pwstring fontName);
		HRESULT LoadFontFile(_pwstring fontFilePath, _pwstring fontName);

	public:
		static FontManager* Create();
		void Remove() override;

	private:
		HRESULT InitializeDWrite();
		HRESULT AddFont(_pwstring fontName, _pFont* ppTextFormat);

	private:
		IDWriteFactory* _pDWriteFactory{ nullptr };
		std::unordered_map<_pwstring, _pFont> _fontMap;
	};
}