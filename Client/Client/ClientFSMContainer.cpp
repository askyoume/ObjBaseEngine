#include "ClientFSMContainer.h"
//state
#include "Idle.h"
#include "Runing.h"
#include "Move.h"
#include "MiddleKick.h"
#include "LowKick.h"
#include "AutoComboStart.h"
#include "BackDash.h"
#include "AirLaunch.h"

//transition
#include "IdleToRuning.h"
#include "IdleToMove.h"
#include "IdleToKick.h"
#include "IdleToMiddleKick.h"
#include "KickToComboStart.h"
#include "StartToAirLaunch.h"


void Client::ClientFSMContainer::ContainStep()
{
	Idle*			idle			= Idle::Create();
	Move*			move			= Move::Create();
	Running*		running			= Running::Create();
	LowKick*		lowKick			= LowKick::Create();
	BackDash*		backDash		= BackDash::Create();
	AirLaunch*		airLaunch		= AirLaunch::Create();
	MiddleKick*		middleKick		= MiddleKick::Create();
	AutoComboStart* autoComboStart	= AutoComboStart::Create();

	IdleToMove*			idleToMove			= IdleToMove::Create();
	IdleToKick*			idleToKick			= IdleToKick::Create();
	IdleToRunning*		idleToRunning		= IdleToRunning::Create();
	IdleToMiddleKick*	idleToMiddleKick	= IdleToMiddleKick::Create();
	KickToComboStart*	kickToComboStart	= KickToComboStart::Create();
	StartToAirLaunch*	startToAirLaunch	= StartToAirLaunch::Create();
	
	autoComboStart->SetPriority(true);
	middleKick->SetPriority(true);
	lowKick->SetPriority(true);

	AddState(idle);
	AddState(move);
	AddState(running);
	AddState(lowKick);
	AddState(backDash);
	AddState(airLaunch);
	AddState(middleKick);
	AddState(autoComboStart);

	SetInitialState("IDLE");

	idle->AddTransition(idleToMove);
	move->AddTransition(idleToRunning);
	lowKick->AddTransition(idleToKick);
	airLaunch->AddTransition(startToAirLaunch);
	middleKick->AddTransition(idleToMiddleKick);
	autoComboStart->AddTransition(kickToComboStart);

	lowKick->BindState(idle);
	lowKick->BindState(move);
	middleKick->BindState(idle);
	middleKick->BindState(move);
	autoComboStart->BindState(idle);
}

void Client::ClientFSMContainer::Update(float deltaSeconds)
{
	StateContainer::Update(deltaSeconds);
}

void Client::ClientFSMContainer::Remove()
{
	StateContainer::Remove();
}

Client::ClientFSMContainer* Client::ClientFSMContainer::Create()
{
	return new ClientFSMContainer;
}
