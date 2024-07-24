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

	_inputEvents.push_back(inputEvent);

	auto iter = _eventHandlers.find(inputEvent.key);
	if (iter == _eventHandlers.end())
		return;

	auto& handlers = iter->second[inputEvent.type];
	for (auto& handler : handlers)
	{
		handler(inputEvent);
	}

	if (_inputEvents.size() > 30)
	{
		_inputEvents.pop_front();
	}
}

void Core::InputComponent::AttachToInputManager()
{
	if(_eventHandlers.empty())
		return;

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

bool Core::InputComponent::IsKeyEventTriggerNow(_uint key, InputType type) const
{
	if (_inputEvents.empty())
		return false;

	if (_inputEvents.back().timeToLastInput > 0.3f)
		return false;

	if (_inputEvents.back().key == key && _inputEvents.back().type == type)
	{
		return true;
	}

	return false;
}

bool Core::InputComponent::IsKeyEventTriggered(_uint key, InputType type) const
{
	if (_inputEvents.empty())
		return false;

	for (auto& inputEvent : _inputEvents)
	{
		if (inputEvent.key == key && inputEvent.type == type)
			return true;
	}

	return false;
}

bool Core::InputComponent::IsLastInputOverTime(_float time) const
{
	if (_inputEvents.empty())
		return false;

	return _inputEvents.back().timeToLastInput > time;
}

bool Core::InputComponent::IsKeyEventTriggeredOverTime(_uint key, InputType type, _float time) const
{
	if (_inputEvents.empty())
		return false;

	for (auto iter = _inputEvents.rbegin(); 
		iter != _inputEvents.rend(); iter++)
	{
		if (iter->key == key && iter->type == type)
		{
			return iter->timeToLastInput > time;
		}
	}

	return false;
}

bool Core::InputComponent::IsKeyEventTriggeredLessTime(_uint key, InputType type, _float time) const
{
	if (_inputEvents.empty())
		return false;

	for (auto iter = _inputEvents.rbegin();
		iter != _inputEvents.rend(); iter++)
	{
		if (iter->key == key && iter->type == type)
		{
			return iter->timeToLastInput < time;
		}
	}

	return false;
}

Core::InputComponent* Core::InputComponent::Create()
{
	InputComponent* pInputComponent = new InputComponent;
	if (pInputComponent->Initialize())
		return pInputComponent;

	return nullptr;
}

bool Core::InputComponent::Initialize()
{
	return true;
}

void Core::InputComponent::TickComponent(_float deltaSeconds)
{
	if (_inputEvents.empty())
		return;

	if(9999.f > _inputEvents.back().timeToLastInput)
	{
		_inputEvents.back().timeToLastInput += deltaSeconds;
	}

	//std::cout << "Time : " << _inputEvents.back().timeToLastInput << std::endl;
}

void Core::InputComponent::Remove()
{
	if(_eventHandlers.empty())
		return;

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

