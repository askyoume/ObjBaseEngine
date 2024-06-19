#pragma once
#include "Core_Define.h"

namespace Core
{
	class GraphicsManager : public Core
	{
	private:
		explicit GraphicsManager() DEFAULT;
		virtual ~GraphicsManager() DEFAULT;

	public:
		HRESULT Initialize(HWND hWnd);
		GraphicsPtrPackage* GetPackage() { return &_pGraphicsPtrPackage; }
		//이 정도면 분리해야됨!
		HRESULT LoadFontFile(_pwstring fontFilePath, _pwstring fontName);

	public:
		static GraphicsManager* Create();
		void Remove() override;

	private:
		HRESULT InitializeD3D(HWND hWnd);
		HRESULT InitializeD2D(HWND hWnd);

	private:
		GraphicsPtrPackage _pGraphicsPtrPackage;
	};
}