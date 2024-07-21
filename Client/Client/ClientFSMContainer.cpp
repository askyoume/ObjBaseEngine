#include "ClientFSMContainer.h"
//state
#include "Idle.h"
#include "Runing.h"
#include "Move.h"
#include "MiddleKick.h"
#include "LowKick.h"
#include "AutoComboStart.h"
//transition
#include "IdleToRuning.h"
#include "IdleToMove.h"
#include "IdleToKick.h"
#include "IdleToMiddleKick.h"
#include "KickToComboStart.h"


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

	AutoComboStart* autoComboStart = AutoComboStart::Create();
	autoComboStart->SetPriority(true);
	AddState(autoComboStart);

	IdleToRunning* idleToRunning = IdleToRunning::Create();
	IdleToMove* idleToMove = IdleToMove::Create();
	IdleToKick* idleToKick = IdleToKick::Create();
	IdleToMiddleKick* idleToMiddleKick = IdleToMiddleKick::Create();
	KickToComboStart* kickToComboStart = KickToComboStart::Create();
	//idle->AddTransition(kickToComboStart);
	idle->AddTransition(idleToMove);
	move->AddTransition(idleToRunning);

	middleKick->AddTransition(idleToMiddleKick);
	middleKick->BindState(idle);
	middleKick->BindState(move);
	middleKick->BindState(running);

	lowKick->AddTransition(idleToKick);
	lowKick->BindState(idle);
	lowKick->BindState(move);
	lowKick->BindState(running);

	autoComboStart->AddTransition(kickToComboStart);
	autoComboStart->BindState(idle);
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
