#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"

#include "Runing.h"
#include "Aoko.h"
#include "AokoFSMContainer.h"

void Client::Runing::Enter()
{
	if(!pAoko)
	{
		pAoko = static_cast<Aoko*>(_pOwnerComponent->GetOwner());
	}
	//std::cout << "Runing Enter" << std::endl;
	Mathf::Vector2 _direction = pAoko->GetDirection();
	::Core::AnimationComponent* pAnimationComponent = 
		pAoko->GetComponent<::Core::AnimationComponent>("AnimationComponent");
	if (_direction.x > 0)
	{
		pAnimationComponent->SetFlip(false);
	}
	else
	{
		pAnimationComponent->SetFlip(true);
	}

	_elapsedTime = 0.f;

	pAoko->SetPlayClip("ReadyToRuning");
}

void Client::Runing::Execute(float deltaTime)
{
	::Core::AnimationComponent* pAnimationComponent = 
		pAoko->GetComponent<::Core::AnimationComponent>("AnimationComponent");

	if(pAnimationComponent->IsClipEnd("ReadyToRuning"))
	{
		pAoko->SetPlayClip("Runing");
	}

	_elapsedTime += deltaTime;

	Mathf::Vector2 _direction = pAoko->GetDirection();

	Mathf::Vector2 _velocity = { _direction.x * _runSpeed * _elapsedTime, 0.f };

	if(_velocity.x > 10.f)
	{
		_velocity.x = 10.f;
	}
	else if (_velocity.x < -10.f)
	{
		_velocity.x = -10.f;
	}

	pAoko->GetRootComponent()->AddRelativeLocation({_velocity.x, 0.f});

	//std::cout << "Runing Execute" << std::endl;
}

void Client::Runing::Exit()
{
		pAoko->SetPlayClip("ReadyToIdle");

		_elapsedTime = 0.f;
	//std::cout << "Runing Exit" << std::endl;
}

void Client::Runing::Remove()
{
}

Client::Runing* Client::Runing::Create()
{
	Runing* runing = new Runing();
	runing->_name = "RUNING";

	return runing;
}
