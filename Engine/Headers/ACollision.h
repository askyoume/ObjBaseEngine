#pragma once
#include "Core_Define.h"
#include "Mathf.h"

class ACollision
{
protected:
	explicit ACollision() = default;
	virtual ~ACollision() = default;
public:
	void SetCollisionSize(const Mathf::Vector2& collisionSize) { _collisionSize = collisionSize; }
	Mathf::Vector2 GetCollisionSize() const { return _collisionSize; }

	void SetCollisionOffset(const Mathf::Vector2& collisionOffset) { _collisionOffset = collisionOffset; }
	Mathf::Vector2 GetCollisionOffset() const { return _collisionOffset; }

	void SetCollisionScale(const Mathf::Vector2& collisionScale);
	Mathf::Vector2 GetCollisionScale() const { return _collisionSize; }

	bool CheckCollision(ACollision* pCollision) const;

public:
	static ACollision* Create() { return new ACollision(); }
	void Release() { delete this; }

private:
	Mathf::Vector2 _collisionSize{ 0.f, 0.f };
	Mathf::Vector2 _collisionOffset{ 0.f, 0.f };
};