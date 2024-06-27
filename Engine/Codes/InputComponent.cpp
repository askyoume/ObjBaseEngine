#include "InputComponent.h"
#include "InputManager.h"
#include "IInputReceiver.h"
#include "CoreManager.h"
#include "Actor.h"

void Core::InputComponent::BindInputEvent(_uint key, InputType type, Callback handler)
{
	_eventHandlers[key][type].push_back(handler);
}

void Core::InputComponent::OnInputReceived(const InputEvent& inputEvent)
{
	if (_owner->IsDestroyMarked())
		return;

	auto iter = _eventHandlers.find(inputEvent.key);
	if (iter == _eventHandlers.end())
		return;

	auto& handlers = iter->second[inputEvent.type];
	for (auto& handler : handlers)
		handler(inputEvent);
}

void Core::InputComponent::AttachToInputManager()
{
	CoreManager* pCore = CoreManager::GetInstance();
	InputManager* Manager = pCore->GetInputManager();

	for (auto& [key, types] : _eventHandlers)
	{
		for (auto& [type, _] : types)
		{
			Manager->RegisterReceiver(key, type, this);
		}
	}
}

void Core::InputComponent::SetVibration(float leftMotor, float rightMotor)
{
	XINPUT_VIBRATION vibration{
		static_cast<WORD>(leftMotor * USHRT_MAX),
		static_cast<WORD>(rightMotor * USHRT_MAX)
	};

	XInputSetState(0, &vibration);
}

void Core::InputComponent::TriggerAction(_pstring actionName)
{
	auto iter = _actions.find(actionName);
	if (iter != _actions.end())
	{
			iter->second->action();
	}
}

void Core::InputComponent::TriggerKeyAction(InputDevice device, _uint key)
{
	auto iter = _keyActions.find({ device, key });
	if (iter != _keyActions.end())
	{
		iter->second->action();
	}
}

Core::InputComponent* Core::InputComponent::Create()
{
	static InputComponent* pInputComponent = new InputComponent;
	if (pInputComponent->Initialize())
		return pInputComponent;

	return nullptr;
}

bool Core::InputComponent::Initialize()
{
	return true;
}

void Core::InputComponent::Remove()
{
	CoreManager* pCore = CoreManager::GetInstance();
	InputManager* Manager = pCore->GetInputManager();

	for (auto& [key, types] : _eventHandlers)
	{
		for (auto& [type, _] : types)
		{
			Manager->UnRegisterReceiver(key, type, this);
		}
	}

	_eventHandlers.clear();
}

