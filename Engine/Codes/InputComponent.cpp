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
	{
		handler(inputEvent);
		//_inputEvents.push_back(inputEvent);
	}
}

void Core::InputComponent::AttachToInputManager()
{
	CoreManager* pCore = CoreManager::GetInstance();

	for (auto& [key, types] : _eventHandlers)
	{
		for (auto& [type, _] : types)
		{
			pCore->RegisterReceiver(key, type, this);
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

	for (auto& [key, types] : _eventHandlers)
	{
		for (auto& [type, _] : types)
		{
			pCore->UnRegisterReceiver(key, type, this);
		}
	}

	_eventHandlers.clear();
}

