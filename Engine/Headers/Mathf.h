#pragma once
#include "Core_Define.h"

struct Vector2 : public D2D1_VECTOR_2F
{
	Vector2() DEFAULT;
	Vector2(float x, float y) : D2D1_VECTOR_2F{ x, y } {}
	Vector2(const D2D1_VECTOR_2F& rhs) : D2D1_VECTOR_2F{ rhs.x, rhs.y } {}

	Vector2(const Vector2& rhs) DEFAULT;
	Vector2(Vector2&& rhs) DEFAULT;

	Vector2 Normalize()
	{
		Vector2 result{ 0.f, 0.f };
		float length = sqrtf(x * x + y * y);
		if(Vector2{0.f, 0.f} == *this)
		{
			return result;
		}

		result.x = x / length;
		result.y = y / length;

		return result;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2 operator=(const Vector2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	bool operator==(const Vector2& rhs)
	{
		return (x == rhs.x) && (y == rhs.y);
	}

	bool operator!=(const Vector2& rhs)
	{
		return (x != rhs.x) || (y != rhs.y);
	}

	Vector2 operator+(const Vector2& rhs)
	{
		return Vector2{ x + rhs.x, y + rhs.y };
	}

	Vector2 operator+(const float& rhs)
	{
		return Vector2{ x + rhs, y + rhs };
	}

	Vector2 operator-(const Vector2& rhs)
	{
		return Vector2{ x - rhs.x, y - rhs.y };
	}

	Vector2 operator-(const float& rhs)
	{
		return Vector2{ x - rhs, y - rhs };
	}

	Vector2 operator*(const float& rhs)
	{
		return Vector2{ x * rhs, y * rhs };
	}

	Vector2 operator/(const float& rhs)
	{
		return Vector2{ x / rhs, y / rhs };
	}

	Vector2 operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2 operator-=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2 operator*=(const float& rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vector2 operator/=(const float& rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	Vector2 operator-()
	{
		return Vector2{ -x, -y };
	}
};

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2{ lhs.x + rhs.x, lhs.y + rhs.y };
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2{ lhs.x - rhs.x, lhs.y - rhs.y };
}

Vector2 operator*(const Vector2& lhs, const float& rhs)
{
	return Vector2{ lhs.x * rhs, lhs.y * rhs };
}

float Dot(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Lerp(const Vector2& start, const Vector2& end, float t)
{
	return start + (end - start) * t;
}

Vector2 Reflect(const Vector2& in, const Vector2& normal)
{
	return in - normal * 2.f * Dot(in, normal);
}

namespace UnitVector
{
	const Vector2 Zero{ 0.f, 0.f };
	const Vector2 One{ 1.f, 1.f };
	const Vector2 Up{ 0.f, -1.f };
	const Vector2 Down{ 0.f, 1.f };
	const Vector2 Left{ -1.f, 0.f };
	const Vector2 Right{ 1.f, 0.f };
}

const float Rad2Deg = 180.f / DirectX::XM_PI;
const float Deg2Rad = DirectX::XM_PI / 180.f;

typedef D2D_MATRIX_3X2_F Matrix3x2;

void GetRotationFormMatrix(const Matrix3x2& matrix, float& angle)
{
	angle = atan2f(matrix._21, matrix._11);
}

void SetRotationToMatrix(Matrix3x2& matrix, float angle)
{
	matrix._11 = cosf(angle);
	matrix._12 = -sinf(angle);
	matrix._21 = sinf(angle);
	matrix._22 = cosf(angle);
}

void GetScaleFormMatrix(const Matrix3x2& matrix, Vector2& scale)
{
	scale.x = sqrtf(matrix._11 * matrix._11 + matrix._21 * matrix._21);
	scale.y = sqrtf(matrix._12 * matrix._12 + matrix._22 * matrix._22);
}

void SetScaleToMatrix(Matrix3x2& matrix, const Vector2& scale)
{
	matrix._11 = scale.x;
	matrix._22 = scale.y;
}

void GetLocationFormMatrix(const Matrix3x2& matrix, Vector2& location)
{
	location.x = matrix._31;
	location.y = matrix._32;
}

void SetPositionToMatrix(Matrix3x2& matrix, const Vector2& location)
{
	matrix._31 = location.x;
	matrix._32 = location.y;
}

typedef D2D_RECT_F Rect;
typedef D2D_POINT_2F Point;

bool CheckCollision(const Rect& lhs, const Rect& rhs)
{
	if(lhs.left < rhs.right && lhs.right > rhs.left &&
		lhs.top < rhs.bottom && lhs.bottom > rhs.top)
	{
		return true;
	}

	return false;
}

bool CheckCollision(const Rect& lhs, const Point& rhs)
{
	if(lhs.left < rhs.x && lhs.right > rhs.x &&
		lhs.top < rhs.y && lhs.bottom > rhs.y)
	{
		return true;
	}

	return false;
}
