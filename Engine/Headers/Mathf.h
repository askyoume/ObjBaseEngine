#pragma once
#include "Matrix.h"

namespace UnitVector
{
	const Mathf::Vector2 Zero{ 0.f, 0.f };
	const Mathf::Vector2 One{ 1.f, 1.f };
	const Mathf::Vector2 Up{ 0.f, -1.f };
	const Mathf::Vector2 Down{ 0.f, 1.f };
	const Mathf::Vector2 Left{ -1.f, 0.f };
	const Mathf::Vector2 Right{ 1.f, 0.f };
}

namespace Mathf
{
	const float Rad2Deg = 180.f / DirectX::XM_PI;
	const float Deg2Rad = DirectX::XM_PI / 180.f;
}

namespace Mathf
{
	typedef D2D_RECT_F Rect;
	typedef D2D_SIZE_F Size;
	typedef D2D_POINT_2F Point;

	inline bool CheckCollision(const Rect& lhs, const Rect& rhs)
	{
		if(lhs.left < rhs.right && lhs.right > rhs.left &&
			lhs.top < rhs.bottom && lhs.bottom > rhs.top)
		{
			return true;
		}

		return false;
	}

	inline bool CheckCollision(const Rect& lhs, const Point& rhs)
	{
		if(lhs.left < rhs.x && lhs.right > rhs.x &&
			lhs.top < rhs.y && lhs.bottom > rhs.y)
		{
			return true;
		}

		return false;
	}
}

