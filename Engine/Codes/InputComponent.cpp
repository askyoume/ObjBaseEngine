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

void Core::InputComponent::SetVibration(float leftMotorSpeed, float rightMotorSpeed)
{
	_vibration.wLeftMotorSpeed = static_cast<_uint>(leftMotorSpeed * USHRT_MAX);
	_vibration.wRightMotorSpeed = static_cast<_uint>(rightMotorSpeed * USHRT_MAX);

	XInputSetState(0, &_vibration);
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

