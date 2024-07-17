#include "ClientFSMContainer.h"
#include "Idle.h"
#include "Runing.h"
#include "Move.h"
#include "IdleToRuning.h"
#include "IdleToMove.h"
#include "MiddleKick.h"
#include "IdleToKick.h"

void Client::ClientFSMContainer::ContainStep()
{
	Idle* idle = Idle::Create();
	AddState(idle);
	SetInitialState("IDLE");

	Runing* runing = Runing::Create();
	AddState(runing);

	Move* move = Move::Create();
	AddState(move);

	MiddleKick* middleKick = MiddleKick::Create();
	middleKick->SetPriority(true);
	AddState(middleKick);

	IdleToRuning* idleToRuning = IdleToRuning::Create();
	IdleToMove* idleToMove = IdleToMove::Create();
	IdleToKick* idleToKick = IdleToKick::Create();
	idle->AddTransition(idleToMove);
	move->AddTransition(idleToRuning);

	middleKick->AddTransition(idleToKick);
	middleKick->BindState(idle);
	middleKick->BindState(move);
	middleKick->BindState(runing);
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
