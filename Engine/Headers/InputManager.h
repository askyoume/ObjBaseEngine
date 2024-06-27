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
		void UnRegisterReceiver(_uint key, InputType Type, IInputReceiver* Receiver);
		XINPUT_STATE* ReturnGamePad() { return _pGamePad; }

	public:
		void ProcessKeyboardInput();
		void ProcessMouseInput();
		void ProcessGamePadInput();

	public:
		void RegisterAction(_pstring actionName, InputComponent* component);
		void UnRegisterAction(_pstring actionName, InputComponent* component);
		void RegisterKey(InputDevice device, _uint key, InputType type, InputComponent* component);
		void UnRegisterKey(InputDevice device, _uint key, InputType type, InputComponent* component);

	public:
		void DispatchInput(InputDevice Device, InputType Type, _uint Key, _float Value = 0.f, bool State = false, long x = 0, long y = 0);
		void DispatchInput(_pstring actionName);
		void DispatchKeyInput(InputDevice device, _uint key);

	public:
		static InputManager* Create();
		void Remove() override;

	private:
		void InitializeKeyboard();
		void InitializeMouse();
		void InitializeGamePad();

	private:
		IDirectInput8* _pInputSDK = nullptr;
		IDirectInputDevice8* _pKeyboard = nullptr;
		IDirectInputDevice8* _pMouse = nullptr;

		XINPUT_STATE* _pGamePad = nullptr;
		DWORD _gamePadIndex = 0;
		HWND hWnd = nullptr;

		float _elapsedTime = 0.f;

		std::unordered_map<_uint, std::unordered_map<InputType, std::vector<IInputReceiver*>>> Receivers;
		std::unordered_map<std::string, std::vector<InputComponent*>> actionReceivers;
        std::unordered_map<std::pair<InputDevice, _uint>, std::vector<InputComponent*>, PairHash> keyReceivers;
	};
}