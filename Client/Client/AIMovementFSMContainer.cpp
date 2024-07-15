#include "AIMovementFSMContainer.h"
#include "AI_Idle.h"
#include "AI_Attack.h"
#include "AI_Chasing.h"
#include "AI_IdleToChasing.h"
#include "AI_IdleToAttack.h"
#include "AI_ChasingToIdle.h"



void Client::AIMovementFSMContainer::ContainStep()
{
	AI_Idle* idle = AI_Idle::Create();
	AddState(idle);
	SetInitialState("AI_IDLE");
	
	AI_Chasing* chasing = AI_Chasing::Create();
	AddState(chasing);

	AI_Attack* attack = AI_Attack::Create();
	AddState(attack);

	AI_IdleToChasing* idleToChasing = AI_IdleToChasing::Create();
	AI_IdleToAttack* idleToAttack = AI_IdleToAttack::Create();
	AI_ChasingToIdle* chasingToIdle = AI_ChasingToIdle::Create();

	idle->AddTransition(idleToChasing);
	chasing->AddTransition(chasingToIdle);
	chasing->AddTransition(idleToAttack);
	attack->AddTransition(chasingToIdle);
}

void Client::AIMovementFSMContainer::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void Client::AIMovementFSMContainer::Remove()
{
	Super::Remove();
}

Client::AIMovementFSMContainer* Client::AIMovementFSMContainer::Create()
{
    return new AIMovementFSMContainer;
}
