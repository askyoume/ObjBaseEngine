#include "ClientWorld.h"
#include "TestActor.h"

bool Client::ClientWorld::BeginPlay()
{
	//test code
    AddActor(1, "TestActor", TestActor::Create());
	//test code end

    return true;
}
