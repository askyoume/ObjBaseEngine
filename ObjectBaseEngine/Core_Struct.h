#pragma once
#include "Core_Define.h"

enum class InputDevice
{
	KEYBOARD,
	MOUSE,
	GAMEPAD,
	JOYSTICK,
	END
};

enum class InputType
{
	PRESS,
	RELEASE,
	HELD,
	AXIS,
	SCROLL,
	MOVE,
	END
};

enum MouseState
{
	DIM_LB = 0,
	DIM_RB = 1,
	DIM_WB = 2,
	DIM_END = 4
};

struct InputEvent
{
	InputDevice device;
	InputType type;
	unsigned int key;
	float value;
	bool state;
	long x, y;

	InputEvent(InputDevice _device, InputType _type, unsigned int _key, float _value, bool _state, long x, long y)
		: device(_device), type(_type), key(_key), value(_value), state(_state), x(x), y(y) {}
};

struct GraphicsPtrPackage
{
	// DirectX 11
	ID3D11Device*			_pDevice{ nullptr };
	ID3D11DeviceContext*	_pDeviceContext{ nullptr };
	ID3D11RenderTargetView* _pRenderTargetView{ nullptr };
	// IDXGI
	IDXGIAdapter*			_pAdapter{ nullptr };
	IDXGIFactory*			_pDXGIFactory{ nullptr };
	IDXGIDevice*			_pDXGIDevice{ nullptr };
	IDXGISwapChain*			_pSwapChain{ nullptr };
	IDXGISurface*			_pBackBuffer{ nullptr };
	// DirectX 2D
	ID2D1Factory*			_pD2DFactory{ nullptr };
	ID2D1RenderTarget*		_pD2DRenderTarget{ nullptr };
	ID2D1SolidColorBrush*	_pBrush{ nullptr };
	ID2D1HwndRenderTarget*  _pHwndRenderTarget{ nullptr };
	// Windows Imaging Component
	IWICImagingFactory*		_pWICFactory{ nullptr };
	// DirectX 2D Text
	IDWriteFactory*			_pDWriteFactory{ nullptr };
	IDWriteTextFormat*		_pTextFormat{ nullptr };
	IDWriteTextLayout*		_pTextLayout{ nullptr };
};

struct BitmapPtrPackage
{
	ID2D1Bitmap*			_pBitmap{ nullptr };
	IWICBitmapDecoder*		_pDecoder{ nullptr };
	IWICFormatConverter*	_pConverter{ nullptr };
	IWICBitmapFrameDecode*	_pFrame{ nullptr };
};