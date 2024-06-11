#pragma once
#include "Vector2.h"

namespace Mathf
{
	typedef D2D_MATRIX_3X2_F Matrix3x2;

	inline void GetRotationFormMatrix(const Matrix3x2& matrix, float& angle)
	{
		angle = atan2f(matrix._21, matrix._11);
	}

	inline void SetRotationToMatrix(Matrix3x2& matrix, float angle)
	{
		matrix._11 = cosf(angle);
		matrix._12 = -sinf(angle);
		matrix._21 = sinf(angle);
		matrix._22 = cosf(angle);
	}

	inline void GetScaleFormMatrix(const Matrix3x2& matrix, Mathf::Vector2& scale)
	{
		scale.x = sqrtf(matrix._11 * matrix._11 + matrix._21 * matrix._21);
		scale.y = sqrtf(matrix._12 * matrix._12 + matrix._22 * matrix._22);
	}

	inline void SetScaleToMatrix(Matrix3x2& matrix, const Mathf::Vector2& scale)
	{
		matrix._11 = scale.x;
		matrix._22 = scale.y;
	}

	inline void GetLocationFormMatrix(const Matrix3x2& matrix, Mathf::Vector2& location)
	{
		location.x = matrix._31;
		location.y = matrix._32;
	}

	inline void SetPositionToMatrix(Matrix3x2& matrix, const Mathf::Vector2& location)
	{
		matrix._31 = location.x;
		matrix._32 = location.y;
	}
}
