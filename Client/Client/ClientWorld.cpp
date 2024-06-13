#include "ClientWorld.h"
#include "TestActor.h"
#include "TestActor2.h"

bool Client::ClientWorld::BeginPlay()
{
	//test code
    AddActor(1, "TestActor", TestActor::Create());

	AddActor(1, "TestActor2", TestActor2::Create());
	//test code end

    return true;
}
