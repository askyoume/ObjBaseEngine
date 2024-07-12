#include "ClientFSMContainer.h"
#include "Idle.h"
#include "Runing.h"
#include "Move.h"
#include "IdleToRuning.h"
#include "IdleToMove.h"

void Client::ClientFSMContainer::ContainStep()
{
	Idle* idle = Idle::Create();
	AddState(idle);
	SetInitialState("IDLE");

	Runing* runing = Runing::Create();
	AddState(runing);

	Move* move = Move::Create();
	AddState(move);

	IdleToRuning* idleToRuning = IdleToRuning::Create();
	IdleToMove* idleToMove = IdleToMove::Create();
	idle->AddTransition(idleToMove);
	move->AddTransition(idleToRuning);
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
