#include "InputManager.h"
#include "Core_Enum.h"
#include "Core_Define.h"
#include "Core_Struct.h"

#include <dinput.h>

bool Core::InputManager::Initialize(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hresult = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_pInputSDK, nullptr);
	if (FAILED(hresult))
	{
		MessageBox(hWnd, L"DirectInput8Create() failed", L"Error", MB_OK);
		return false;
	}

	this->hWnd = hWnd;

	InitializeKeyboard();
	InitializeMouse();
	InitializeGamePad();

	return true;
}

void Core::InputManager::InputUpdate()
{
	if(_pKeyboard)
	{
		ProcessKeyboardInput();
	}

	if(_pMouse)
	{
		ProcessMouseInput();
	}

	if(_pGamePad)
	{
		ProcessGamePadInput();
	}
}

void Core::InputManager::Remove()
{
	if (_pKeyboard)
    {
        _pKeyboard->Unacquire();
        _pKeyboard->Release();
        _pKeyboard = nullptr;
    }
    if (_pMouse)
    {
        _pMouse->Unacquire();
        _pMouse->Release();
        _pMouse = nullptr;
    }
    if (_pGamePad)
    {
        _pGamePad->Unacquire();
        _pGamePad->Release();
        _pGamePad = nullptr;
    }
    if (_pInputSDK)
    {
        _pInputSDK->Release();
        _pInputSDK = nullptr;
    }
}

void Core::InputManager::RegisterReceiver(_uint key, InputType Type, IInputReceiver* Receiver)
{
	Receivers[key][Type].push_back(Receiver);
}

void Core::InputManager::InitializeKeyboard()
{
	HRESULT hresult = _pInputSDK->CreateDevice(GUID_SysKeyboard, &_pKeyboard, nullptr);
	if(SUCCEEDED(hresult))
	{
		hresult = _pKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if(SUCCEEDED(hresult))
		{
			hresult = _pKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			if(SUCCEEDED(hresult))
			{
				_pKeyboard->Acquire();
				if(FAILED(hresult))
				{
					MessageBox(hWnd, L"Keyboard Acquire() failed", L"Error", MB_OK);
					_pKeyboard->Release();
					_pKeyboard = nullptr;
				}
			}
			else
			{
				MessageBox(hWnd, L"Keyboard SetCooperativeLevel() failed", L"Error", MB_OK);
				_pKeyboard->Release();
				_pKeyboard = nullptr;
			}
		}
		else
		{
			MessageBox(hWnd, L"Keyboard SetDataFormat() failed", L"Error", MB_OK);
			_pKeyboard->Release();
			_pKeyboard = nullptr;
		}
	}
	else
	{
		MessageBox(hWnd, L"CreateDevice() failed", L"Error", MB_OK);
		_pKeyboard->Release();
		_pKeyboard = nullptr;
	}
}

void Core::InputManager::InitializeMouse()
{
	HRESULT hresult = _pInputSDK->CreateDevice(GUID_SysMouse, &_pMouse, nullptr);
	if(SUCCEEDED(hresult))
	{
		hresult = _pMouse->SetDataFormat(&c_dfDIMouse);
		if(SUCCEEDED(hresult))
		{
			hresult = _pMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			if(SUCCEEDED(hresult))
			{
				_pMouse->Acquire();
				if(FAILED(hresult))
				{
					MessageBox(hWnd, L"Mouse Acquire() failed", L"Error", MB_OK);
					_pMouse->Release();
					_pMouse = nullptr;
				}
			}
			else
			{
				MessageBox(hWnd, L"Mouse SetCooperativeLevel() failed", L"Error", MB_OK);
				_pMouse->Release();
				_pMouse = nullptr;
			}
		}
		else
		{
			MessageBox(hWnd, L"Mouse SetDataFormat() failed", L"Error", MB_OK);
			_pMouse->Release();
			_pMouse = nullptr;
		}
	}
	else
	{
		MessageBox(hWnd, L"CreateDevice() failed", L"Error", MB_OK);
		_pMouse->Release();
		_pMouse = nullptr;
	}
}

void Core::InputManager::InitializeGamePad()
{
	_pInputSDK->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumGamepadsCallback, this, DIEDFL_ATTACHEDONLY);
}

BOOL Core::InputManager::EnumGamepadsCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	InputManager* pThis = static_cast<InputManager*>(pvRef);
	HRESULT hresult = pThis->_pInputSDK->CreateDevice(lpddi->guidInstance, &pThis->_pGamePad, nullptr);
	if(SUCCEEDED(hresult))
	{
		hresult = pThis->_pGamePad->SetDataFormat(&c_dfDIJoystick);
		if(SUCCEEDED(hresult))
		{
			hresult = pThis->_pGamePad->SetCooperativeLevel(pThis->hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			if(SUCCEEDED(hresult))
			{
				pThis->_pGamePad->Acquire();
				if(FAILED(hresult))
				{
					MessageBox(pThis->hWnd, L"GamePad Acquire() failed", L"Error", MB_OK);
					pThis->_pGamePad->Release();
					pThis->_pGamePad = nullptr;
				}
			}
			else
			{
				MessageBox(pThis->hWnd, L"GamePad SetCooperativeLevel() failed", L"Error", MB_OK);
				pThis->_pGamePad->Release();
				pThis->_pGamePad = nullptr;
			}
		}
		else
		{
			MessageBox(pThis->hWnd, L"GamePad SetDataFormat() failed", L"Error", MB_OK);
			pThis->_pGamePad->Release();
			pThis->_pGamePad = nullptr;
		}
	}
	return DIENUM_STOP;
}

void Core::InputManager::ProcessKeyboardInput()
{
	_byte keyState[256]{};
	HRESULT hresult = _pKeyboard->GetDeviceState(sizeof(keyState), (LPVOID)&keyState);
	if(FAILED(hresult))
	{
		if(hresult == DIERR_INPUTLOST || hresult == DIERR_NOTACQUIRED)
		{
			_pKeyboard->Acquire();
		}
	}
	else
	{
		for(_uint i = 0; i < 256; i++)
		{
			bool isPressed = (keyState[i] & 0x80) != 0;
			DispatchInput(InputDevice::KEYBOARD, isPressed ? InputType::PRESS : InputType::RELEASE, i, 0.f, isPressed);
		}
	}
}

void Core::InputManager::ProcessMouseInput()
{
	DIMOUSESTATE mouseState{};
	HRESULT hresult = _pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
	if(FAILED(hresult))
	{
		if(hresult == DIERR_INPUTLOST || hresult == DIERR_NOTACQUIRED)
		{
			_pMouse->Acquire();
		}
	}
	else
	{
		for (_uint i = 0; i < DIM_END; ++i)
        {
            bool isPressed = (mouseState.rgbButtons[i] & 0x80) != 0;
            DispatchInput(InputDevice::MOUSE, isPressed ? InputType::PRESS : InputType::RELEASE, i, 0.0f, isPressed);
        }

        if (mouseState.lZ != 0)
        {
            DispatchInput(InputDevice::MOUSE, InputType::SCROLL, 0, static_cast<float>(mouseState.lZ));
        }

        if (mouseState.lX != 0 || mouseState.lY != 0)
        {
            DispatchInput(InputDevice::MOUSE, InputType::MOVE, 0, 0.0f, false, mouseState.lX, mouseState.lY);
        }
	}
}

void Core::InputManager::ProcessGamePadInput()
{
	if(_pGamePad)
	{
		DIJOYSTATE2 gamePadState{};
		HRESULT hresult = _pGamePad->GetDeviceState(sizeof(DIJOYSTATE2), (LPVOID)&gamePadState);
		if(FAILED(hresult))
		{
			if(hresult == DIERR_INPUTLOST || hresult == DIERR_NOTACQUIRED)
			{
				_pMouse->Acquire();
			}
		}
		else
		{
			for(_uint i = 0; i < 128; ++i)
			{
				bool isPressed = (gamePadState.rgbButtons[i] & 0x80) != 0;
				DispatchInput(InputDevice::GAMEPAD, isPressed ? InputType::PRESS : InputType::RELEASE, i, 0.f, isPressed);
			}

			if(gamePadState.lX != 0)
			{
				DispatchInput(InputDevice::GAMEPAD, InputType::AXIS, 0, static_cast<_float>(gamePadState.lX));
			}

			if(gamePadState.lY != 0)
			{
				DispatchInput(InputDevice::GAMEPAD, InputType::AXIS, 1, static_cast<_float>(gamePadState.lY));
			}
		}
	}
}

void Core::InputManager::DispatchInput(InputDevice Device, InputType Type, _uint Key, _float Value, bool State, long x, long y)
{
	InputEvent event(Device, Type, Key, Value, State, x, y);
	auto find = Receivers.find(Key);
	if(find != Receivers.end())
	{
		auto findType = find->second.find(Type);
		if(findType != find->second.end())
		{
			for(auto& receiver : findType->second)
			{
				receiver->OnInputReceived(event);
			}
		}
	}
}

Core::InputManager* Core::InputManager::Create()
{
	return new InputManager();
}


