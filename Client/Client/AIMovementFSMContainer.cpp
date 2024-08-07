#include "AIMovementFSMContainer.h"

#include "AI_Idle.h"
#include "AI_Attack.h"
#include "AI_Chasing.h"
#include "AI_Hit.h"
#include "AI_Dead.h"

#include "AI_IdleToChasing.h"
#include "AI_IdleToAttack.h"
#include "AI_ChasingToIdle.h"
#include "AI_IdleToHit.h"
#include "AI_AllToDeath.h"



void Client::AIMovementFSMContainer::ContainStep()
{
	AI_Idle* idle = AI_Idle::Create();
	AddState(idle);
	SetInitialState("AI_IDLE");
	
	AI_Chasing* chasing = AI_Chasing::Create();
	AddState(chasing);

	AI_Attack* attack = AI_Attack::Create();
	AddState(attack);

	AI_Hit* hit = AI_Hit::Create();
	hit->SetPriority(true);
	AddState(hit);

	AI_Dead* dead = AI_Dead::Create();
	dead->SetPriority(true);
	AddState(dead);

	AI_IdleToChasing* idleToChasing = AI_IdleToChasing::Create();
	AI_IdleToAttack* idleToAttack = AI_IdleToAttack::Create();
	AI_ChasingToIdle* chasingToIdle = AI_ChasingToIdle::Create();
	AI_IdleToHit* idleToHit = AI_IdleToHit::Create();
	AI_AllToDeath* allToDeath = AI_AllToDeath::Create();

	idle->AddTransition(idleToChasing);
	chasing->AddTransition(chasingToIdle);
	chasing->AddTransition(idleToAttack);
	attack->AddTransition(chasingToIdle);

	hit->AddTransition(idleToHit);
	hit->BindState(idle);
	hit->BindState(chasing);
	hit->BindState(attack);

	dead->AddTransition(allToDeath);
	dead->BindState(idle);
	dead->BindState(chasing);
	dead->BindState(attack);
	dead->BindState(hit);
}

void Client::AIMovementFSMContainer::Update(float deltaSeconds)
{
	Super::Update(deltaSeconds);
}

void Client::AIMovementFSMContainer::Remove()
{
	Super::Remove();
}

Client::AIMovementFSMContainer* Client::AIMovementFSMContainer::Create()
{
    return new AIMovementFSMContainer;
}
