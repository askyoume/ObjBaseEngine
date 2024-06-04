#include "InputComponent.h"
#include "InputManager.h"
#include "IInputReceiver.h"
#include "CoreManager.h"

void Core::InputComponent::BindInputEvent(_uint key, InputType type, Callback handler)
{
	_eventHandlers[key][type].push_back(handler);
}

void Core::InputComponent::OnInputReceived(const InputEvent& inputEvent)
{
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

void Core::InputComponent::Remove()
{
	_eventHandlers.clear();
}

