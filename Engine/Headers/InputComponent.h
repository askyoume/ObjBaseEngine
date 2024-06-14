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
		using Callback = std::function<void(const InputEvent&)>;
		std::unordered_map<_uint, std::unordered_map<InputType, std::vector<Callback>>> _eventHandlers;

	public:
		void BindInputEvent(_uint key, InputType type, Callback handler);
		void OnInputReceived(const InputEvent& inputEvent) override; // IInputReceiver �������̽� ������
		void AttachToInputManager();
		void SetVibration(float leftMotorSpeed, float rightMotorSpeed);

	public:
		static InputComponent* Create();/* { return new InputComponent; }*/

	private:
		void BeginPlay() override {};
		bool Initialize() override;
		void TickComponent(_float deltaTime) override {};
		void EndPlay() override {};
		void Remove() override;

	private:
		XINPUT_VIBRATION _vibration{ 0, 0 };
	};
}