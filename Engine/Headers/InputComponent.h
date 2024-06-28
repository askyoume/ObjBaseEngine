#pragma once
#include "Core_Define.h"
#include "Component.h"
#include "IInputReceiver.h"

namespace Core
{
	class InputComponent : public Component, public IInputReceiver
	{
	protected:
		explicit InputComponent() DEFAULT;
		virtual ~InputComponent() DEFAULT;

	public:
		using Action = std::function<void()>;
		using ActionMap = std::unordered_map<_pstring, InputAction*>;
		using KeyActionMap = std::unordered_map<std::pair<InputDevice, _uint>, InputAction*, PairHash>;
		using Callback = std::function<void(const InputEvent&)>;
		std::unordered_map<_uint, std::unordered_map<InputType, std::vector<Callback>>> _eventHandlers;

	public:
		void BindInputEvent(_uint key, InputType type, Callback handler);
		void OnInputReceived(const InputEvent& inputEvent) override; // IInputReceiver 인터페이스 구현부
		void AttachToInputManager();
		void SetVibration(float leftMotor, float rightMotor);

		template <typename T, typename F>
		InputAction* BindAction(_pstring actionName, T* object, F function)
		{
			InputAction* result = new InputAction{ 
				actionName, false, [object, function]() { (object->*function)(); 
				}};

			_actions[actionName].push_back(result);

		}

		template <typename T, typename F>
		void BindAction(InputDevice device, _uint key, T* object, F function)
		{
			_keyActions[{device, key}] = BindAction(_pstring{ device, key }, object, function);
		}

		void TriggerAction(_pstring actionName);
		void TriggerKeyAction(InputDevice device, _uint key);


	public:
		static InputComponent* Create();

	private:
		void BeginPlay() override {};
		bool Initialize() override;
		void TickComponent(_float deltaTime) override {};
		void EndPlay() override {};
		void Remove() override;

	private:
		KeyActionMap _keyActions;
		ActionMap _actions;
	};
}