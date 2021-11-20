/*****************************************************************//**
 * \file   Util_Mathf.h
 * \brief  算術
 *
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#include "Util_Mathf.h"


#ifdef _WIN32


#else
const Vector2 Vector2::zero = Vector2{ 0,0 };
const Vector2 Vector2::one = Vector2{ 1,1 };
const Vector2 Vector2::right = Vector2{ 1,0 };
const Vector2 Vector2::up = Vector2{ 0,1 };
 
const Vector3 Vector3::zero = Vector3{ 0,0,0 };
const Vector3 Vector3::one = Vector3{ 1,1,1 };
const Vector3 Vector3::right = Vector3{ 1,0,0 };
const Vector3 Vector3::up = Vector3{ 0,1,0 };
const Vector3 Vector3::forward = Vector3{ 0,0,1 };

const Vector4 Vector4::zero = Vector4{ 0,0,0,0 };
const Vector4 Vector4::one = Vector4{ 1,1,1,1 };

const Matrix Matrix::Identity;


// マトリックス適用
Vector3 Vector3::Transform(const Vector3& vec, const class Matrix& mat, float w)
{
	Vector3 retVal;
	retVal.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] +
		vec.z * mat.m[2][0] + w * mat.m[3][0];
	retVal.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] +
		vec.z * mat.m[2][1] + w * mat.m[3][1];
	retVal.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] +
		vec.z * mat.m[2][2] + w * mat.m[3][2];
	//ignore w since we aren't returning a new value for it...
	return retVal;
}

// 逆行列
void Matrix::Invert() noexcept
{
	float tmp[12];
	float src[16];
	float dst[16];
	float det;

	// row 1 to col 1
	src[0] = m[0][0];
	src[4] = m[0][1];
	src[8] = m[0][2];
	src[12] = m[0][3];

	// row 2 to col 2
	src[1] = m[1][0];
	src[5] = m[1][1];
	src[9] = m[1][2];
	src[13] = m[1][3];

	// row 3 to col 3
	src[2] = m[2][0];
	src[6] = m[2][1];
	src[10] = m[2][2];
	src[14] = m[2][3];

	// row 4 to col 4
	src[3] = m[3][0];
	src[7] = m[3][1];
	src[11] = m[3][2];
	src[15] = m[3][3];

	// Calculate cofactors
	tmp[0] = src[10] * src[15];
	tmp[1] = src[11] * src[14];
	tmp[2] = src[9] * src[15];
	tmp[3] = src[11] * src[13];
	tmp[4] = src[9] * src[14];
	tmp[5] = src[10] * src[13];
	tmp[6] = src[8] * src[15];
	tmp[7] = src[11] * src[12];
	tmp[8] = src[8] * src[14];
	tmp[9] = src[10] * src[12];
	tmp[10] = src[8] * src[13];
	tmp[11] = src[9] * src[12];

	dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
	dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
	dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
	dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
	dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
	dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
	dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
	dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
	dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

	tmp[0] = src[2] * src[7];
	tmp[1] = src[3] * src[6];
	tmp[2] = src[1] * src[7];
	tmp[3] = src[3] * src[5];
	tmp[4] = src[1] * src[6];
	tmp[5] = src[2] * src[5];
	tmp[6] = src[0] * src[7];
	tmp[7] = src[3] * src[4];
	tmp[8] = src[0] * src[6];
	tmp[9] = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];

	dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
	dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
	dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
	dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
	dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
	dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
	dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
	dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
	dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
	dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
	dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
	dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
	dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
	dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
	dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
	dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

	// Calculate determinant
	det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

	// Inverse of matrix is divided by determinant
	det = 1 / det;
	for (int j = 0; j < 16; j++)
	{
		dst[j] *= det;
	}

	// Set it back
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = dst[i * 4 + j];
		}
	}
}
#endif // _WIN32
