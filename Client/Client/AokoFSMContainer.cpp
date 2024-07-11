#include "AokoFSMContainer.h"
#include "Idle.h"
#include "Runing.h"
#include "IdleToRuning.h"

void Client::AokoFSMContainer::ContainStep()
{
	Idle* idle = Idle::Create();
	AddState(idle);
	SetInitialState("IDLE");

	Runing* runing = Runing::Create();
	AddState(runing);

	IdleToRuning* idleToRuning = IdleToRuning::Create();
	idle->AddTransition(idleToRuning);
	//runing->AddTransition(idleToRuning);
}

void Client::AokoFSMContainer::Update(float deltaTime)
{
	StateContainer::Update(deltaTime);
}

void Client::AokoFSMContainer::Remove()
{
	StateContainer::Remove();
}

Client::AokoFSMContainer* Client::AokoFSMContainer::Create()
{
	return new AokoFSMContainer;
}
