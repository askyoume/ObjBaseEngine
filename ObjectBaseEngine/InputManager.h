#pragma once
#include "Core_Define.h"
#include "IInputReceiver.h"

namespace Core
{
	CORECLASS()
	class InputManager : public Core
	{
	private:
		InputManager() DEFAULT;
		~InputManager() DEFAULT;

	public:
		bool Initialize(HINSTANCE hInst, HWND hWnd);
		void InputUpdate();
		void RegisterReceiver(_uint key, InputType Type, IInputReceiver* Receiver);
		void RegisterInputComponent(_uint key, InputType Type, IInputReceiver* Receiver);

	public:
		void ProcessKeyboardInput();
		void ProcessMouseInput();
		void ProcessGamePadInput();

	public:
		void DispatchInput(InputDevice Device, InputType Type, _uint Key, _float Value = 0.f, bool State = false, long x = 0, long y = 0);

	public:
		static InputManager* Create();
		void Remove() override;

	private:
		void InitializeKeyboard();
		void InitializeMouse();
		void InitializeGamePad();
		static BOOL CALLBACK EnumGamepadsCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);

	private:
		IDirectInput8* _pInputSDK = nullptr;
		IDirectInputDevice8* _pKeyboard = nullptr;
		IDirectInputDevice8* _pMouse = nullptr;
		IDirectInputDevice8* _pGamePad = nullptr;
		HWND hWnd = nullptr;

		std::unordered_map<_uint, std::unordered_map<InputType, std::vector<IInputReceiver*>>> Receivers;
	};
}