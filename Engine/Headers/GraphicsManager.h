#pragma once
#include "Core_Define.h"

namespace Core
{
	class GraphicsManager : public Core
	{
	private:
		explicit GraphicsManager() = default;
		virtual ~GraphicsManager() = default;

	public:
		HRESULT Initialize(HWND hWnd);
		GraphicsPtrPackage* GetPackage() { return &_pGraphicsPtrPackage; }

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