#pragma once
#include "Core_Define.h"
#include "Component.h"
#include "IInputReceiver.h"

namespace Core
{
	class InputComponent : public Component, public IInputReceiver
	{
	protected:
		explicit InputComponent() = default;
		virtual ~InputComponent() = default;

	protected:
		using Callback = std::function<void(const InputEvent&)>;
		std::unordered_map<_uint, std::unordered_map<InputType, std::vector<Callback>>> _eventHandlers;
		std::deque<InputEvent> _inputEvents;

	public:
		void BindInputEvent(_uint key, InputType type, Callback handler);
		void OnInputReceived(const InputEvent& inputEvent) override; // IInputReceiver 인터페이스 구현부
		void AttachToInputManager();
		void SetVibration(float leftMotor, float rightMotor);
		bool IsKeyPress(_uint key, InputType type) const;
		bool IsKeyPressed(_uint key, InputType type) const;

		template<typename T, typename U>
		void BindAction(_uint key, InputType type, T* object, void (U::*method)(const InputEvent&))
		{
			Callback handler = [object, method](const InputEvent& inputEvent)
				{
					(object->*method)(inputEvent);
				};
			_eventHandlers[key][type].push_back(handler);
		}

	public:
		static InputComponent* Create();

	private:
		void BeginPlay() override {};
		bool Initialize() override;
		void TickComponent(_float deltaTime) override {};
		void EndPlay() override {};
		void Remove() override;
	};
}