#include "GraphicsManager.h"
#include "CoreManager.h"

HRESULT Core::GraphicsManager::Initialize(HWND hWnd)
{
	HRESULT hresult = S_OK;

	/*hresult = InitializeD3D(hWnd);
	if (FAILED(hresult))
	{
		return hresult;
	}*/

	hresult = InitializeD2D(hWnd);
	if (FAILED(hresult))
	{
		return hresult;
	}

	return hresult;
}

Core::GraphicsManager* Core::GraphicsManager::Create()
{
	return new GraphicsManager;
}

void Core::GraphicsManager::Remove()
{
	if (_pGraphicsPtrPackage._pBrush)
	{
		_pGraphicsPtrPackage._pBrush->Release();
		_pGraphicsPtrPackage._pBrush = nullptr;
	}
	if (_pGraphicsPtrPackage._pD2DRenderTarget)
	{
		_pGraphicsPtrPackage._pD2DRenderTarget->Release();
		_pGraphicsPtrPackage._pD2DRenderTarget = nullptr;
	}
	if (_pGraphicsPtrPackage._pD2DFactory)
	{
		_pGraphicsPtrPackage._pD2DFactory->Release();
		_pGraphicsPtrPackage._pD2DFactory = nullptr;
	}
	if (_pGraphicsPtrPackage._pBackBuffer)
	{
		_pGraphicsPtrPackage._pBackBuffer->Release();
		_pGraphicsPtrPackage._pBackBuffer = nullptr;
	}
	if (_pGraphicsPtrPackage._pSwapChain)
	{
		_pGraphicsPtrPackage._pSwapChain->Release();
		_pGraphicsPtrPackage._pSwapChain = nullptr;
	}
	if (_pGraphicsPtrPackage._pDXGIFactory)
	{
		_pGraphicsPtrPackage._pDXGIFactory->Release();
		_pGraphicsPtrPackage._pDXGIFactory = nullptr;
	}
	if (_pGraphicsPtrPackage._pDXGIDevice)
	{
		_pGraphicsPtrPackage._pDXGIDevice->Release();
		_pGraphicsPtrPackage._pDXGIDevice = nullptr;
	}
	if (_pGraphicsPtrPackage._pAdapter)
	{
		_pGraphicsPtrPackage._pAdapter->Release();
		_pGraphicsPtrPackage._pAdapter = nullptr;
	}
	if (_pGraphicsPtrPackage._pDeviceContext)
	{
		_pGraphicsPtrPackage._pDeviceContext->Release();
		_pGraphicsPtrPackage._pDeviceContext = nullptr;
	}
	if (_pGraphicsPtrPackage._pDevice)
	{
		_pGraphicsPtrPackage._pDevice->Release();
		_pGraphicsPtrPackage._pDevice = nullptr;
	}
}

HRESULT Core::GraphicsManager::InitializeD3D(HWND hWnd)
{
	CoreManager* _pCoreMgr = CoreManager::GetInstance();

	HRESULT hresult = S_OK;

	hresult = D3D11CreateDevice(
		_pGraphicsPtrPackage._pAdapter, 
		D3D_DRIVER_TYPE_HARDWARE, 
		nullptr, 
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, 
		nullptr, 
		NULL, 
		D3D11_SDK_VERSION, 
		&_pGraphicsPtrPackage._pDevice, 
		nullptr, 
		&_pGraphicsPtrPackage._pDeviceContext
	);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to create D3D11 device.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pGraphicsPtrPackage._pDevice->QueryInterface(&_pGraphicsPtrPackage._pDevice);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to create D3D11 device.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pGraphicsPtrPackage._pDevice->QueryInterface(&_pGraphicsPtrPackage._pDXGIDevice);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to create DXGI device.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pGraphicsPtrPackage._pDXGIDevice->GetAdapter(&_pGraphicsPtrPackage._pAdapter);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to get DXGI adapter.", L"Error", MB_OK);
		return hresult;
	}

	_pGraphicsPtrPackage._pAdapter->GetParent(IID_PPV_ARGS(&_pGraphicsPtrPackage._pDXGIFactory));
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to get DXGI factory.", L"Error", MB_OK);
		return hresult;
	}

	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(swapDesc));

	swapDesc.BufferDesc.Width = static_cast<_uint>(_pCoreMgr->GetWidth());
	swapDesc.BufferDesc.Height = static_cast<_uint>(_pCoreMgr->GetHeight());
	swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = BUFFER_END;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.OutputWindow = hWnd;
	swapDesc.Windowed = TRUE;

	hresult = _pGraphicsPtrPackage._pDXGIFactory->CreateSwapChain(
		_pGraphicsPtrPackage._pDevice, &swapDesc, &_pGraphicsPtrPackage._pSwapChain);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to create swap chain.", L"Error", MB_OK);
		return hresult;
	}

	ID3D11Texture2D* pBackBuffer{ nullptr };
	hresult = _pGraphicsPtrPackage._pSwapChain->GetBuffer(
		BACKBUFFER, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer
	);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to get back buffer.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pGraphicsPtrPackage._pDevice->CreateRenderTargetView(
		pBackBuffer, nullptr, &_pGraphicsPtrPackage._pRenderTargetView
	);
	if (FAILED(hresult))
	{
		pBackBuffer->Release();
		MessageBoxW(hWnd, L"Failed to create render target view.", L"Error", MB_OK);
		return hresult;
	}

	pBackBuffer->Release();
		
	return S_OK;
}

HRESULT Core::GraphicsManager::InitializeD2D(HWND hWnd)
{
	CoreManager* _pCoreMgr = CoreManager::GetInstance();

	HRESULT hresult = S_OK;
	float dpi{};

	hresult = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_pGraphicsPtrPackage._pWICFactory)
	);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to create WIC factory.", L"Error", MB_OK);
		return hresult;
	}


	hresult = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, 
		&_pGraphicsPtrPackage._pD2DFactory
	);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to create D2D factory.", L"Error", MB_OK);
		return hresult;
	}

	dpi = static_cast<float>(GetDpiForWindow(hWnd));

	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = 
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
			dpi,
			dpi
	);

	//hresult = _pGraphicsPtrPackage._pSwapChain->GetBuffer(
	//	BACKBUFFER, IID_PPV_ARGS(&_pGraphicsPtrPackage._pBackBuffer)
	//);
	//if (FAILED(hresult))
	//{
	//	MessageBoxW(hWnd, L"Failed to get back buffer.", L"Error", MB_OK);
	//	return hresult;
	//}
	//
	//hresult = 
	//	_pGraphicsPtrPackage._pD2DFactory->CreateDxgiSurfaceRenderTarget(
	//		_pGraphicsPtrPackage._pBackBuffer,
	//		renderTargetProperties,
	//		&_pGraphicsPtrPackage._pD2DRenderTarget
	//);
	//if (FAILED(hresult))
	//{
	//	MessageBoxW(hWnd, L"Failed to create D2D render target.", L"Error", MB_OK);
	//	return hresult;
	//}

	//hresult = _pGraphicsPtrPackage._pD2DRenderTarget->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::White),
	//	&_pGraphicsPtrPackage._pBrush
	//);
	//if (FAILED(hresult))
	//{
	//	MessageBoxW(hWnd, L"Failed to create D2D brush.", L"Error", MB_OK);
	//	return hresult;
	//}

	hresult = _pGraphicsPtrPackage._pD2DFactory->CreateHwndRenderTarget(
		renderTargetProperties,
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(_pCoreMgr->GetWidth(), _pCoreMgr->GetHeight())),
		&_pGraphicsPtrPackage._pHwndRenderTarget
	);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to create D2D render target.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pGraphicsPtrPackage._pHwndRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&_pGraphicsPtrPackage._pBrush
	);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to create D2D brush.", L"Error", MB_OK);
		return hresult;
	}

	hresult = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&_pGraphicsPtrPackage._pDWriteFactory
	);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to create DWrite factory.", L"Error", MB_OK);
		return hresult;
	}

	hresult = _pGraphicsPtrPackage._pDWriteFactory->CreateTextFormat(
		L"Arial",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		16.0f,
		L"en-us",
		&_pGraphicsPtrPackage._pTextFormat
	);

	return hresult;
}
