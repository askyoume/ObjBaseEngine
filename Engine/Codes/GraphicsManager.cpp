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
		SafeRelease(_pGraphicsPtrPackage._pBrush);
	}
	if (_pGraphicsPtrPackage._pD2DRenderTarget)
	{
		SafeRelease(_pGraphicsPtrPackage._pD2DRenderTarget);
	}
	if (_pGraphicsPtrPackage._pRenderTargetView)
	{
		SafeRelease(_pGraphicsPtrPackage._pRenderTargetView);
	}
	if (_pGraphicsPtrPackage._pD2DFactory)
	{
		SafeRelease(_pGraphicsPtrPackage._pD2DFactory);
	}
	if (_pGraphicsPtrPackage._pBackBuffer)
	{
		SafeRelease(_pGraphicsPtrPackage._pBackBuffer);
	}
	if (_pGraphicsPtrPackage._pSwapChain)
	{
		SafeRelease(_pGraphicsPtrPackage._pSwapChain);
	}
	if(_pGraphicsPtrPackage._pHwndRenderTarget)
	{
		SafeRelease(_pGraphicsPtrPackage._pHwndRenderTarget);
	}
	if (_pGraphicsPtrPackage._pDXGIFactory)
	{
		SafeRelease(_pGraphicsPtrPackage._pDXGIFactory);
	}
	if (_pGraphicsPtrPackage._pDXGIDevice)
	{
		SafeRelease(_pGraphicsPtrPackage._pDXGIDevice);
	}
	if (_pGraphicsPtrPackage._pAdapter)
	{
		SafeRelease(_pGraphicsPtrPackage._pAdapter);
	}
	if (_pGraphicsPtrPackage._pDeviceContext)
	{
		SafeRelease(_pGraphicsPtrPackage._pDeviceContext);
	}
	if (_pGraphicsPtrPackage._pDevice)
	{
		SafeRelease(_pGraphicsPtrPackage._pDevice);
	}

	CoUninitialize();
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
			D2D1_RENDER_TARGET_TYPE_HARDWARE,
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

	D2D1_SIZE_U screenSize = D2D1::SizeU(
		(_uint)_pCoreMgr->GetWidth(), 
		(_uint)_pCoreMgr->GetHeight()
	);

	D2D1_PRESENT_OPTIONS presentOptions = D2D1_PRESENT_OPTIONS_IMMEDIATELY;
	//D2D1_PRESENT_OPTIONS presentOptions = D2D1_PRESENT_OPTIONS_NONE;

	hresult = _pGraphicsPtrPackage._pD2DFactory->CreateHwndRenderTarget(
		renderTargetProperties,
		D2D1::HwndRenderTargetProperties(hWnd, screenSize, presentOptions),
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

	return hresult;
}
