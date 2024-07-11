#include "ClientFSMContainer.h"
#include "Idle.h"
#include "Runing.h"
#include "IdleToRuning.h"

void Client::ClientFSMContainer::ContainStep()
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

void Client::ClientFSMContainer::Update(float deltaTime)
{
	StateContainer::Update(deltaTime);
}

void Client::ClientFSMContainer::Remove()
{
	StateContainer::Remove();
}

Client::ClientFSMContainer* Client::ClientFSMContainer::Create()
{
	return new ClientFSMContainer;
}
