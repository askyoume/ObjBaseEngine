#pragma once //temp
#include "../Engine/Headers/Core_Define.h"
#include "../Engine/Headers/Component.h"
#include "../Engine/Headers/Mathf.h"

namespace Core
{
	CORECLASS()
	class MovementComponent : public Component
	{
	protected:
		explicit MovementComponent() DEFAULT;
		virtual ~MovementComponent() DEFAULT;

	public:
		virtual bool Initialize() override;
		virtual void BeginPlay() override;
		virtual void TickComponent(_float deltaTime) override;
		virtual void EndPlay() override;
		virtual void Remove() override{};

	public:
		void Move(float deltaTime);
		void Jump(float deltaTime);

	public:
		void SetRootComponent(SceneComponent* pRootComponent) { _pRootComponent = pRootComponent; }
		void SetInputDirection(Mathf::Vector2 inputDirection) { _inputDirection = inputDirection; }
		Mathf::Vector2 GetInputDirection() const { return _inputDirection; }

	public:
		void SetGroundPosition(float groundPosition) { _groundPosition = groundPosition; }
		void SetMoveSpeed(float moveSpeed) { _moveSpeed = moveSpeed; }
		void SetGravityFactor(float gravityFactor) { _gravityFactor = gravityFactor; }
		void SetLimitSpeed(float limitSpeed) { _limitSpeed = limitSpeed; }
		void SetJumpPower(float jumpPower) { _jumpPower = jumpPower; }

	public:
		static MovementComponent* Create();
	
	protected:
		SceneComponent* _pRootComponent{ nullptr };
		Mathf::Vector2 _inputDirection{ UnitVector::Zero };
		Mathf::Vector2 _velocity{ 0.f, 0.f };
		Mathf::Vector2 _gravityVector{ 0.f, 0.f };

	protected:
		const float _gravity{ 9.8f };

	protected:
		float _moveSpeed{ 0.f };
		float _gravityFactor{ 0.f };
		float _limitSpeed{ 0.f };
		float _calculatedGravity{ 0.f };
		float _jumpPower{ 0.f };
		float _groundPosition{ 0.f };

	protected:
		bool _isJumping{ false };
		bool _isGrounded{ true };
	};
}