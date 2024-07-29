#pragma once
#include "Core_Define.h"
#include "Component.h"
#include "Mathf.h"

namespace Core
{
	CORECLASS()
	class MovementComponent : public Component
	{
	protected:
		explicit MovementComponent() = default;
		virtual ~MovementComponent() = default;

	public:
		virtual bool Initialize() override;
		virtual void BeginPlay() override;
		virtual void TickComponent(_float deltaSeconds) override;
		virtual void EndPlay() override;
		virtual void Remove() override{};

	public:
		void Move(float deltaSeconds);
		void Run(float deltaSeconds);
		void Jump(float deltaSeconds);
		void DiagonalMove(float deltaSeconds);

	public:
		void SetRootComponent(SceneComponent* pRootComponent) { _pRootComponent = pRootComponent; }
		void SetInputDirection(Mathf::Vector2 inputDirection) { _inputDirection = inputDirection; }
		void SetInputDirectionX(float x) { _inputDirection.x = x; }
		void SetInputDirectionY(float y) { _inputDirection.y = y; }
		Mathf::Vector2 GetInputDirection() const { return _inputDirection; }
		Mathf::Vector2& ChangeVelocity() { return _velocity; }

	public:
		void SetGroundPosition(float groundPosition) { _groundPosition = groundPosition; }
		void SetMoveSpeed(float moveSpeed) { _moveSpeed = moveSpeed; }
		void SetGravityFactor(float gravityFactor) { _gravityFactor = gravityFactor; }
		void SetLimitSpeed(float limitSpeed) { _limitSpeed = limitSpeed; }
		void SetJumpPower(float jumpPower) { _jumpPower = jumpPower; }
		void SetRunning(bool isRunning) { _isRunning = isRunning; }

	public:
		bool IsGrounded() const { return _isGrounded; }
		bool IsJumping() const { return _isJumping; }
		bool IsRunning() const { return _isRunning; }

		void SetGrounded(bool isGrounded) { _isGrounded = isGrounded; }

	public:
		static MovementComponent* Create();
	
	protected:
		SceneComponent* _pRootComponent{ nullptr };
		Mathf::Vector2 _inputDirection{ UnitVector::Zero };
		Mathf::Vector2 _velocity{ UnitVector::Zero };
		Mathf::Vector2 _gravityVector{ UnitVector::Zero };
		Mathf::Vector2 _ownerPreviousLocation{ UnitVector::Zero };
		Mathf::Vector2 _ownerCurrentLocation{ UnitVector::Zero };

	protected:
		const float _gravity{ 9.8f };

	protected:
		float _friction{ 0.f };
		float _acceleration{ 0.f };
		float _targetSpeed{ 0.f };
		float _moveSpeed{ 0.f };
		float _limitSpeed{ 0.f };
		float _calculatedGravity{ 0.f };
		float _jumpPower{ 0.f };
		float _groundPosition{ 0.f };

	protected:
		float _moveSpeedFactor{ 0.f };
		float _gravityFactor{ 0.f };

	protected:
		bool _isJumping{ false };
		bool _isGrounded{ true };
		bool _isRunning{ false };
	};
}