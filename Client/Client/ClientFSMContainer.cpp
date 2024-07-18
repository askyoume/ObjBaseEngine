#include "ClientFSMContainer.h"
//state
#include "Idle.h"
#include "Runing.h"
#include "Move.h"
#include "MiddleKick.h"
#include "LowKick.h"
//transition
#include "IdleToRuning.h"
#include "IdleToMove.h"
#include "IdleToKick.h"

void Client::ClientFSMContainer::ContainStep()
{
	Idle* idle = Idle::Create();
	AddState(idle);
	SetInitialState("IDLE");

	Running* running = Running::Create();
	AddState(running);

	Move* move = Move::Create();
	AddState(move);

	MiddleKick* middleKick = MiddleKick::Create();
	middleKick->SetPriority(true);
	AddState(middleKick);

	LowKick* lowKick = LowKick::Create();
	lowKick->SetPriority(true);
	AddState(lowKick);

	IdleToRunning* idleToRunning = IdleToRunning::Create();
	IdleToMove* idleToMove = IdleToMove::Create();
	IdleToKick* idleToKick = IdleToKick::Create();
	idle->AddTransition(idleToMove);
	move->AddTransition(idleToRunning);

	middleKick->AddTransition(idleToKick);
	middleKick->BindState(idle);
	middleKick->BindState(move);
	middleKick->BindState(running);

	lowKick->AddTransition(idleToKick);
	lowKick->BindState(idle);
	lowKick->BindState(move);
	lowKick->BindState(running);
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
