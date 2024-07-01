#include "InputManager.h"
#include "Core_Enum.h"
#include "Core_Define.h"
#include "Core_Struct.h"
#include "CoreManager.h"
#include "TimeManager.h"
#include "InputComponent.h"

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
		SafeRelease(_pKeyboard);
    }
    if (_pMouse)
    {
        _pMouse->Unacquire();
		SafeRelease(_pMouse);
    }
    if (_pGamePad)
    {
		ZeroMemory(_pGamePad, sizeof(XINPUT_STATE));
		delete _pGamePad;
        _pGamePad = nullptr;
    }
    if (_pInputSDK)
    {
		SafeRelease(_pInputSDK);
    }
}

void Core::InputManager::RegisterReceiver(_uint key, InputType Type, IInputReceiver* Receiver)
{
	Receivers[key][Type].push_back(Receiver);
}

void Core::InputManager::UnRegisterReceiver(_uint key, InputType Type, IInputReceiver* Receiver)
{
	auto find = Receivers.find(key);
	if (find != Receivers.end())
	{
		auto findType = find->second.find(Type);
		if (findType != find->second.end())
		{
			auto findReceiver = std::find(findType->second.begin(), findType->second.end(), Receiver);
			if (findReceiver != findType->second.end())
			{
				findType->second.erase(findReceiver);
			}
		}
	}
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
	_pGamePad = new XINPUT_STATE();
	ZeroMemory(_pGamePad, sizeof(XINPUT_STATE));
	for (_uint i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		DWORD result = XInputGetState(i, _pGamePad);
		if (result == ERROR_SUCCESS)
		{
			_gamePadIndex = i;
			break;
		}
	}
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
			bool isArrowKey = (i == DIK_LEFT || i == DIK_RIGHT || i == DIK_UP || i == DIK_DOWN);
			bool isPressed = (keyState[i] & 0x80) != 0;

			if(isArrowKey && isPressed)
			{
				if (i == DIK_LEFT || i == DIK_RIGHT)
				{
					float AxisValue_X = i == DIK_LEFT ? -1.f : 1.f;
					DispatchInput(InputDevice::KEYBOARD, InputType::AXIS, DIK_AXIS, 0.f, isPressed, (long)AxisValue_X);
				}
				else if (i == DIK_UP || i == DIK_DOWN)
				{
					float AxisValue_Y = i == DIK_UP ? -1.f : 1.f;
					DispatchInput(InputDevice::KEYBOARD, InputType::AXIS, DIK_AXIS, 0.f, isPressed, 0, (long)AxisValue_Y);
				}
			}
			else
			{
				DispatchInput(InputDevice::KEYBOARD, isPressed ? InputType::PRESS : InputType::RELEASE, i, 0.f, isPressed);
			}
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
            DispatchInput(InputDevice::MOUSE, InputType::SCROLL, (_uint)InputType::SCROLL, static_cast<float>(mouseState.lZ));
        }

        if (mouseState.lX != 0 || mouseState.lY != 0)
        {
            DispatchInput(InputDevice::MOUSE, InputType::MOVE, (_uint)InputType::MOVE, 0.0f, false, mouseState.lX, mouseState.lY);
        }
	}
}

void Core::InputManager::ProcessGamePadInput()
{
	if (XInputGetState(_gamePadIndex, _pGamePad) == ERROR_SUCCESS)
	{
		for (_uint i = 0; i < DIP_MAX; i++)
		{
			bool isPressed = (_pGamePad->Gamepad.wButtons & (1 << i)) != 0;
			/*DispatchInput(InputDevice::GAMEPAD, isPressed ? InputType::PRESS : InputType::RELEASE, i, 0.f, isPressed);*/
			if (isPressed && !_previousButtonStates[i])
            {
                DispatchInput(InputDevice::GAMEPAD, InputType::PRESS, i, 0.f, true);
            }
            else if (isPressed && _previousButtonStates[i])
            {
                DispatchInput(InputDevice::GAMEPAD, InputType::HELD, i, 0.f, true);
            }
            else if (!isPressed && _previousButtonStates[i])
            {
                DispatchInput(InputDevice::GAMEPAD, InputType::RELEASE, i, 0.f, false);
            }

			_previousButtonStates[i] = isPressed;
		}

		float gamePadLX = static_cast<float>(_pGamePad->Gamepad.sThumbLX) / GAMEPAD_NORMALIZE;
		if (abs(_pGamePad->Gamepad.sThumbLX) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			DispatchInput(InputDevice::GAMEPAD, InputType::AXIS, DIP_LX, gamePadLX);
		}

		float gamePadLY = static_cast<float>(_pGamePad->Gamepad.sThumbLY) / GAMEPAD_NORMALIZE;
		if (abs(_pGamePad->Gamepad.sThumbLY) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			DispatchInput(InputDevice::GAMEPAD, InputType::AXIS, DIP_LY, -gamePadLY);
		}

		float gamePadRX = static_cast<float>(_pGamePad->Gamepad.sThumbRX) / GAMEPAD_NORMALIZE;
		if (abs(_pGamePad->Gamepad.sThumbRX) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			DispatchInput(InputDevice::GAMEPAD, InputType::AXIS, DIP_RX, gamePadRX);
		}

		float gamePadRY = static_cast<float>(_pGamePad->Gamepad.sThumbRY) / GAMEPAD_NORMALIZE;
		if (abs(_pGamePad->Gamepad.sThumbRY) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			DispatchInput(InputDevice::GAMEPAD, InputType::AXIS, DIP_RY, -gamePadRY);
		}

		float gamePadLT = static_cast<float>(_pGamePad->Gamepad.bLeftTrigger);
		if (gamePadLT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			DispatchInput(InputDevice::GAMEPAD, InputType::TRIGGER, DIP_LT, gamePadLT);
		}
		else
		{
			XINPUT_VIBRATION vibration{};
			XInputSetState(_gamePadIndex, &vibration);
		}

		float gamePadRT = static_cast<float>(_pGamePad->Gamepad.bRightTrigger);
		if (gamePadRT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			DispatchInput(InputDevice::GAMEPAD, InputType::TRIGGER, DIP_RT, gamePadRT);
		}
		else
		{
			XINPUT_VIBRATION vibration{};
			XInputSetState(_gamePadIndex, &vibration);
		}
	}
}

void Core::InputManager::DispatchInput(InputDevice Device, InputType Type, _uint Key, _float Value, bool State, long x, long y)
{
	_uint uniqueKey = (static_cast<_uint>(Device) << 16 | Key);
	InputEvent event(Device, Type, uniqueKey, Value, State, x, y);
	auto find = Receivers.find(uniqueKey);
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


