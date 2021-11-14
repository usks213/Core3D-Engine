/*****************************************************************//**
 * \file   Util_Mathf.h
 * \brief  �Z�p
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/
#ifndef _UTIL_MATHF_
#define _UTIL_MATHF_


#include <cmath>
#include <memory>
#include <limits>

//#ifdef near
//#undef near
//#endif // near
//#ifdef far
//#undef far
//#endif // far

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace Mathf
{
	constexpr float Pi = 3.1415926535f;
	constexpr float TwoPi = Pi * 2.0f;

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template <typename T>
	T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}

	inline float Lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	//// X����]
	//Vector3 RotationX(const Vector3& vec, float angle)
	//{
	//	float rad = ToRadians(angle);
	//	Vector3 v = vec;

	//	v.y = vec.y * cosf(rad) + vec.z * sinf(rad);
	//	v.z = -vec.y * sinf(rad) + vec.z * cosf(rad);

	//	return v;
	//}

	//// Y����]
	//Vector3 RotationY(const Vector3& vec, float angle)
	//{
	//	float rad = ToRadians(angle);
	//	Vector3 v = vec;

	//	v.x = vec.x * cosf(rad) - vec.z * sinf(rad);
	//	v.z = vec.x * sinf(rad) + vec.z * cosf(rad);

	//	return v;
	//}

	//// Z����]
	//Vector3 RotationZ(const Vector3& vec, float angle)
	//{
	//	float rad = ToRadians(angle);
	//	Vector3 v = vec;

	//	v.x = vec.x * cosf(rad) + vec.y * sinf(rad);
	//	v.y = -vec.x * sinf(rad) + vec.y * cosf(rad);

	//	return v;
	//}
}

class Vector2
{
public:
	float x, y;

	Vector2()
		:x(0.0f)
		, y(0.0f)
	{}

	explicit Vector2(float inX, float inY)
		:x(inX)
		, y(inY)
	{}

	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;
	Vector2& operator=(Vector2&&) = default;

	void Set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

public:
	Vector2 operator - () const { return Vector2(-x, -y); }

	// binay operator +-*/
	Vector2 operator + (const Vector2& v2) const
	{
		return Vector2(x + v2.x, y + v2.y);
	}
	Vector2 operator - (const Vector2& v2) const
	{
		return Vector2(x - v2.x, y - v2.y);
	}
	Vector2 operator * (float s) const
	{
		return Vector2(x * s, y * s);
	}
	Vector2 operator / (float s) const
	{
		return Vector2(x / s, y / s);
	}

	// binay operator += -= *= /=
	Vector2& operator += (const Vector2& v2)
	{
		x += v2.x;
		y += v2.y;
		return *this;
	}
	Vector2 operator -= (const Vector2& v2)
	{
		x -= v2.x;
		y -= v2.y;
		return *this;
	}
	Vector2 operator *= (float s)
	{
		x *= s;
		y *= s;
		return *this;
	}
	Vector2 operator /= (float s)
	{
		x /= s;
		y /= s;
		return *this;
	}

	/// @brief �x�N�g���̒���(���)
	float LengthSq()
	{
		return x * x + y * y;
	}
	/// @brief �x�N�g���̒���
	float Length()
	{
		return sqrtf(LengthSq());
	}
	// �x�N�g���̐��K��
	Vector2 Normalize()
	{
		Vector2 vec = *this;
		float mag = vec.Length();
		if (!mag) return vec;
		vec.x /= mag;
		vec.y /= mag;
		return vec;
	}

public:
	// ����
	static float Dot(const Vector2& vec1, const Vector2& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}
	// ���`���
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
	{
		return Vector2(a + (b - a) * f);
	}
	// ���˃x�N�g��
	static Vector2 Reflect(const Vector2& front, const Vector2& normal)
	{
		return (front - normal * Dot(front, normal) * 2.0f);
	}
	// �����x�N�g��
	static Vector2 Vertical(const Vector2& front, const Vector2& normal)
	{
		return normal * Dot(front, normal);
	}
	// �ǂ���x�N�g��
	static Vector2 Horizontal(const Vector2& front, const Vector2& normal)
	{
		return (front - normal * Dot(front, normal));
	}

	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 right;
	static const Vector2 up;
};

/// @brief Vector3
class Vector3
{
public:
	float x,y,z;

	Vector3()
		:x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}

	explicit Vector3(float inX, float inY, float inZ)
		:x(inX)
		, y(inY)
		, z(inZ)
	{}

	Vector3(const Vector3&) = default;
	Vector3& operator=(const Vector3&) = default;

	Vector3(Vector3&&) = default;
	Vector3& operator=(Vector3&&) = default;

	void Set(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}

public:
	Vector3 operator - () const { return Vector3(-x, -y, -z); }

	Vector3 operator + (const Vector3& v2) const
	{
		return Vector3(x + v2.x, y + v2.y, z + v2.z);
	}
	Vector3 operator - (const Vector3& v2) const
	{
		return Vector3(x - v2.x, y - v2.y, z - v2.z);
	}
	Vector3 operator * (float s) const
	{
		return Vector3(x * s, y * s, z * s);
	}
	Vector3 operator / (float s) const
	{
		return Vector3(x / s, y / s, z / s);
	}
	Vector3& operator += (const Vector3& v2)
	{
		x += v2.x;
		y += v2.y;
		z += v2.z;
		return *this;
	}
	Vector3 operator -= (const Vector3& v2)
	{
		x -= v2.x;
		y -= v2.y;
		z -= v2.z;
		return *this;
	}
	Vector3 operator *= (float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	Vector3 operator /= (float s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

public:
	// �x�N�g���̒���(���)
	float LengthSq()
	{
		return x * x + y * y + z * z;
	}
	// �x�N�g���̒���
	float Length()
	{
		return sqrtf(LengthSq());
	}
	// �x�N�g���̐��K��
	Vector3 Normalize()
	{
		Vector3 vec = *this;
		float mag = vec.Length();
		if (!mag) return vec;
		vec.x /= mag;
		vec.y /= mag;
		vec.z /= mag;
		return vec;
	}

public:
	// ����
	static float Dot(const Vector3& vec1, const Vector3& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}
	// �O��
	static Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		Vector3 temp;
		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;
		return temp;
	}
	// ���`���
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
	{
		return Vector3(a + (b - a) * f);
	}
	// ���˃x�N�g��
	static Vector3 Reflect(const Vector3& front, const Vector3& normal)
	{
		return (front - normal * Dot(front, normal) * 2.0f);
	}
	// �����x�N�g��
	static Vector3 Vertical(const Vector3& front, const Vector3& normal)
	{
		return normal * Dot(front, normal);
	}
	// �ǂ���x�N�g��
	static Vector3 Horizontal(const Vector3& front, const Vector3& normal)
	{
		return (front - normal * Dot(front, normal));
	}

	// �}�g���b�N�X�K�p
	static Vector3 Transform(const Vector3& vec, const class Matrix& mat, float w = 1.0f);
	// ��](�N�H�[�^�j�I��)�K�p
	//static Vector3 Transform(const Vector3& v, const class Quaternion& q);

	static const Vector3 zero;
	static const Vector3 one;
	static const Vector3 right;
	static const Vector3 up;
	static const Vector3 forward;
};

// Vector4
class Vector4
{
public:
	float x, y, z,w;

	Vector4()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{}

	explicit Vector4(float inX, float inY, float inZ, float inW)
		: x(inX)
		, y(inY)
		, z(inZ)
		, w(inW)
	{}

	Vector4(const Vector4&) = default;
	Vector4& operator=(const Vector4&) = default;

	Vector4(Vector4&&) = default;
	Vector4& operator=(Vector4&&) = default;

	void Set(float inX, float inY, float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}

public:
	Vector4 operator - () const { return Vector4(-x, -y, -z, -w); }

	Vector4 operator + (const Vector4& v2) const
	{
		return Vector4(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
	}
	Vector4 operator - (const Vector4& v2) const
	{
		return Vector4(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
	}
	Vector4 operator * (float s) const
	{
		return Vector4(x * s, y * s, z * s, w * s);
	}
	Vector4 operator / (float s) const
	{
		return Vector4(x / s, y / s, z / s, w / s);
	}
	Vector4& operator += (const Vector4& v2)
	{
		x += v2.x;
		y += v2.y;
		z += v2.z;
		w += v2.w;
		return *this;
	}
	Vector4 operator -= (const Vector4& v2)
	{
		x -= v2.x;
		y -= v2.y;
		z -= v2.z;
		w -= v2.w;
		return *this;
	}
	Vector4 operator *= (float s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	Vector4 operator /= (float s)
	{
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}

public:
	// �x�N�g���̒���(���)
	float LengthSq()
	{
		return x * x + y * y + z * z + w * w;
	}
	// �x�N�g���̒���
	float Length()
	{
		return sqrtf(LengthSq());
	}
	// �x�N�g���̐��K��
	Vector4 Normalize()
	{
		Vector4 vec = *this;
		float mag = vec.Length();
		if (!mag) return vec;
		vec.x /= mag;
		vec.y /= mag;
		vec.z /= mag;
		vec.w /= mag;
		return vec;
	}

public:
	// ����
	static float Dot(const Vector4& vec1, const Vector4& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z * vec1.w * vec2.w;
	}
	// �O��
	static Vector4 Cross(const Vector4& a, const Vector4& b)
	{
		Vector4 temp;
		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;
		temp.w = 0.0f;
		return temp;
	}
	// ���`���
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float f)
	{
		return Vector4(a + (b - a) * f);
	}
	// ���˃x�N�g��
	static Vector4 Reflect(const Vector4& front, const Vector4& normal)
	{
		return (front - normal * Dot(front, normal) * 2.0f);
	}
	// �����x�N�g��
	static Vector4 Vertical(const Vector4& front, const Vector4& normal)
	{
		return normal * Dot(front, normal);
	}
	// �ǂ���x�N�g��
	static Vector4 Horizontal(const Vector4& front, const Vector4& normal)
	{
		return (front - normal * Dot(front, normal));
	}

	// �}�g���b�N�X�K�p
	//static Vector4 Transform(const Vector4& vec, const class Matrix& mat, float w = 1.0f);
	// ��](�N�H�[�^�j�I��)�K�p
	//static Vector4 Transform(const Vector4& v, const class Quaternion& q);

	static const Vector4 zero;
	static const Vector4 one;
};

// �}�g���b�N�X4x4
class Matrix
{
public:
	union 
	{
		struct 
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};

	Matrix() noexcept
		: _11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f)
		, _21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f)
		, _31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f)
		, _41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
	{}

	constexpr Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) noexcept
		: _11(m00),_12(m01),_13(m02),_14(m03)
		, _21(m10),_22(m11),_23(m12),_24(m13)
		, _31(m20),_32(m21),_33(m22),_34(m23)
		, _41(m30),_42(m31),_43(m32),_44(m33)
	{}

	explicit Matrix(const Vector3& r0, const Vector3& r1, const Vector3& r2) noexcept
		: Matrix(r0.x, r0.y, r0.z, 0,
			r1.x, r1.y, r1.z, 0,
			r2.x, r2.y, r2.z, 0,
			0, 0, 0, 1.f) {}

	explicit Matrix(const Vector4& r0, const Vector4& r1, const Vector4& r2, const Vector4& r3) noexcept
		: Matrix(r0.x, r0.y, r0.z, r0.w,
			r1.x, r1.y, r1.z, r1.w,
			r2.x, r2.y, r2.z, r2.w,
			r3.x, r3.y, r3.z, r3.w) {}

	Matrix(const Matrix&) = default;
	Matrix& operator=(const Matrix&) = default;

	Matrix(Matrix&&) = default;
	Matrix& operator=(Matrix&&) = default;

public:
	friend Matrix operator*(const Matrix& a, const Matrix& b) noexcept
	{
		Matrix retVal;
		// row 0
		retVal.m[0][0] =
			a.m[0][0] * b.m[0][0] +
			a.m[0][1] * b.m[1][0] +
			a.m[0][2] * b.m[2][0] +
			a.m[0][3] * b.m[3][0];

		retVal.m[0][1] =
			a.m[0][0] * b.m[0][1] +
			a.m[0][1] * b.m[1][1] +
			a.m[0][2] * b.m[2][1] +
			a.m[0][3] * b.m[3][1];

		retVal.m[0][2] =
			a.m[0][0] * b.m[0][2] +
			a.m[0][1] * b.m[1][2] +
			a.m[0][2] * b.m[2][2] +
			a.m[0][3] * b.m[3][2];

		retVal.m[0][3] =
			a.m[0][0] * b.m[0][3] +
			a.m[0][1] * b.m[1][3] +
			a.m[0][2] * b.m[2][3] +
			a.m[0][3] * b.m[3][3];

		// row 1
		retVal.m[1][0] =
			a.m[1][0] * b.m[0][0] +
			a.m[1][1] * b.m[1][0] +
			a.m[1][2] * b.m[2][0] +
			a.m[1][3] * b.m[3][0];

		retVal.m[1][1] =
			a.m[1][0] * b.m[0][1] +
			a.m[1][1] * b.m[1][1] +
			a.m[1][2] * b.m[2][1] +
			a.m[1][3] * b.m[3][1];

		retVal.m[1][2] =
			a.m[1][0] * b.m[0][2] +
			a.m[1][1] * b.m[1][2] +
			a.m[1][2] * b.m[2][2] +
			a.m[1][3] * b.m[3][2];

		retVal.m[1][3] =
			a.m[1][0] * b.m[0][3] +
			a.m[1][1] * b.m[1][3] +
			a.m[1][2] * b.m[2][3] +
			a.m[1][3] * b.m[3][3];

		// row 2
		retVal.m[2][0] =
			a.m[2][0] * b.m[0][0] +
			a.m[2][1] * b.m[1][0] +
			a.m[2][2] * b.m[2][0] +
			a.m[2][3] * b.m[3][0];

		retVal.m[2][1] =
			a.m[2][0] * b.m[0][1] +
			a.m[2][1] * b.m[1][1] +
			a.m[2][2] * b.m[2][1] +
			a.m[2][3] * b.m[3][1];

		retVal.m[2][2] =
			a.m[2][0] * b.m[0][2] +
			a.m[2][1] * b.m[1][2] +
			a.m[2][2] * b.m[2][2] +
			a.m[2][3] * b.m[3][2];

		retVal.m[2][3] =
			a.m[2][0] * b.m[0][3] +
			a.m[2][1] * b.m[1][3] +
			a.m[2][2] * b.m[2][3] +
			a.m[2][3] * b.m[3][3];

		// row 3
		retVal.m[3][0] =
			a.m[3][0] * b.m[0][0] +
			a.m[3][1] * b.m[1][0] +
			a.m[3][2] * b.m[2][0] +
			a.m[3][3] * b.m[3][0];

		retVal.m[3][1] =
			a.m[3][0] * b.m[0][1] +
			a.m[3][1] * b.m[1][1] +
			a.m[3][2] * b.m[2][1] +
			a.m[3][3] * b.m[3][1];

		retVal.m[3][2] =
			a.m[3][0] * b.m[0][2] +
			a.m[3][1] * b.m[1][2] +
			a.m[3][2] * b.m[2][2] +
			a.m[3][3] * b.m[3][2];

		retVal.m[3][3] =
			a.m[3][0] * b.m[0][3] +
			a.m[3][1] * b.m[1][3] +
			a.m[3][2] * b.m[2][3] +
			a.m[3][3] * b.m[3][3];

		return retVal;
	}

	Matrix& operator*=(const Matrix& right)
	{
		*this = *this * right;
		return *this;
	}

public:
	Vector3 Up() const noexcept { return Vector3(_21, _22, _23); }
	void Up(const Vector3& v) noexcept { _21 = v.x; _22 = v.y; _23 = v.z; }

	Vector3 Down() const  noexcept { return Vector3(-_21, -_22, -_23); }
	void Down(const Vector3& v) noexcept { _21 = -v.x; _22 = -v.y; _23 = -v.z; }

	Vector3 Right() const noexcept { return Vector3(_11, _12, _13); }
	void Right(const Vector3& v) noexcept { _11 = v.x; _12 = v.y; _13 = v.z; }

	Vector3 Left() const noexcept { return Vector3(-_11, -_12, -_13); }
	void Left(const Vector3& v) noexcept { _11 = -v.x; _12 = -v.y; _13 = -v.z; }

	Vector3 Forward() const noexcept { return Vector3(-_31, -_32, -_33); }
	void Forward(const Vector3& v) noexcept { _31 = -v.x; _32 = -v.y; _33 = -v.z; }

	Vector3 Backward() const noexcept { return Vector3(_31, _32, _33); }
	void Backward(const Vector3& v) noexcept { _31 = v.x; _32 = v.y; _33 = v.z; }

	Vector3 Translation() const  noexcept { return Vector3(_41, _42, _43); }
	void Translation(const Vector3& v) noexcept { _41 = v.x; _42 = v.y; _43 = v.z; }

	// �]�u
	Matrix Transpose() const noexcept
	{
		return Matrix(
			_11, _21, _31, _41,
			_12, _22, _32, _42,
			_13, _23, _33, _43,
			_14, _24, _34, _44
		);
	}
	// �t�s��
	void Invert() noexcept;

public:
	// �X�P�[��
	static Matrix CreateScale(float xScale, float yScale, float zScale)
	{
		return Matrix(
			xScale, 0.0f, 0.0f, 0.0f,
			0.0f, yScale, 0.0f, 0.0f,
			0.0f, 0.0f, zScale, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	}
	static Matrix CreateScale(const Vector3& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
	}
	static Matrix CreateScale(float scale)
	{
		return CreateScale(scale, scale, scale);
	}

	// ��]
	static Matrix CreateRotationX(float theta)
	{
		return Matrix(
			1.0f, 0.0f, 0.0f , 0.0f,
			0.0f, cosf(theta), sinf(theta), 0.0f,
			0.0f, -sinf(theta), cosf(theta), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	static Matrix CreateRotationY(float theta)
	{
		return Matrix(
			cosf(theta), 0.0f, -sinf(theta), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sinf(theta), 0.0f, cosf(theta), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	static Matrix CreateRotationZ(float theta)
	{
		return Matrix(
			cosf(theta), sinf(theta), 0.0f, 0.0f,
			-sinf(theta), cosf(theta), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	static Matrix CreateRotationZXY(Vector3 theta)
	{
		Matrix mat = CreateRotationZ(theta.z);
		mat *= CreateRotationX(theta.x);
		mat *= CreateRotationY(theta.y);
		return mat;
	}
	static Matrix CreateRotationZXY(float x, float y, float z)
	{
		Matrix mat = CreateRotationZ(z);
		mat *= CreateRotationX(x);
		mat *= CreateRotationY(y);
		return mat;
	}

	// �ړ�
	static Matrix CreateTranslation(const Vector3& trans)
	{
		return Matrix(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			trans.x, trans.y, trans.z, 1.0f
		);
	}

	// �r���[
	static Matrix CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 zaxis = (target - eye).Normalize();
		Vector3 xaxis = Vector3::Cross(up, zaxis).Normalize();
		Vector3 yaxis = Vector3::Cross(zaxis, xaxis).Normalize();
		Vector3 trans;
		trans.x = -Vector3::Dot(xaxis, eye);
		trans.y = -Vector3::Dot(yaxis, eye);
		trans.z = -Vector3::Dot(zaxis, eye);

		return Matrix(
			xaxis.x, yaxis.x, zaxis.x, 0.0f,
			xaxis.y, yaxis.y, zaxis.y, 0.0f,
			xaxis.z, yaxis.z, zaxis.z, 0.0f,
			trans.x, trans.y, trans.z, 1.0f
		);
	}

	// ���s���e
	static Matrix CreateOrtho(float width, float height, float fNear, float fFar)
	{
		return Matrix(
			2.0f / width, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / height, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f / (fFar - fNear), 0.0f,
			0.0f, 0.0f, fNear / (fNear - fFar), 1.0f
		);
	}
	// �������e
	static Matrix CreatePerspectiveFOV(float fovY, float width, float height, float fNear, float fFar)
	{
		float yScale = 1.0f / tanf(fovY / 2.0f);
		float xScale = yScale * height / width;
		return Matrix(
			xScale, 0.0f, 0.0f, 0.0f,
			0.0f, yScale, 0.0f, 0.0f,
			0.0f, 0.0f, fFar / (fFar - fNear), 1.0f,
			0.0f, 0.0f, -fNear * fFar / (fFar - fNear), 0.0f
		);
	}

	static const Matrix Identity;
};

struct VectorUint2
{
	VectorUint2() {
		x = y = 0;
	}

	int x, y;
};
struct VectorUint3
{
	VectorUint3() {
		x = y = z = 0;
	}

	int x, y, z;
};
struct VectorUint4
{
	VectorUint4() {
		x = y = z = w = 0;
	}

	int x, y, z, w;
};

class Color : public Vector4
{
public:
	Color() : Vector4()
	{}

	explicit Color(float r, float g, float b, float a) :
		Vector4(r, g, b, a)
	{}

	Color(const Color&) = default;
	Color& operator=(const Color&) = default;

	Color(Color&&) = default;
	Color& operator=(Color&&) = default;

	void Set(float r, float g, float b, float a)
	{
		x = r;
		y = g;
		z = b;
		w = a;
	}
};

class Rect
{
public:
	Rect() :
		left(0.0f), top(0.0f),
		right(0.0f), bottom(0.0f)
	{}

	Rect(float left, float top, float right, float bottom) :
		left(left), top(top), right(right), bottom(bottom)
	{}

public:

	float left, top;
	float right, bottom;
};

class Viewport : public Rect
{
public:
	Viewport() :
		Rect(), minDepth(0.0f), maxDepth(1.0f)
	{}

	Viewport(float left, float top, float right, float bottom, float minDepth = 0.0f, float maxDepth = 1.0f) :
		Rect(left, top, right, bottom), minDepth(minDepth), maxDepth(maxDepth)
	{}

public:
	float minDepth, maxDepth;
};

class AABB {
	public:
		Vector3 min;
		Vector3 max;

		AABB() :
			min(-0.5f, -0.5f, -0.5f),
			max(0.5f, 0.5f, 0.5f)
		{
		}

	public:
		Vector3 center() const { return (max + min) * 0.5f; };
		Vector3 size() const { return max - min; };

		//static void transformAABB(const Matrix& mWorld, const AABB& sourceAABB, AABB& outAABB) {
		//	Vector3 pos[8] = {
		//		// ���
		//		{ sourceAABB.max.x, sourceAABB.max.y, sourceAABB.max.z },
		//		{ sourceAABB.min.x, sourceAABB.max.y, sourceAABB.max.z },
		//		{ sourceAABB.max.x, sourceAABB.max.y, sourceAABB.min.z },
		//		{ sourceAABB.min.x, sourceAABB.max.y, sourceAABB.min.z },
		//		// ����
		//		{ sourceAABB.max.x, sourceAABB.min.y, sourceAABB.max.z },
		//		{ sourceAABB.min.x, sourceAABB.min.y, sourceAABB.max.z },
		//		{ sourceAABB.max.x, sourceAABB.min.y, sourceAABB.min.z },
		//		{ sourceAABB.min.x, sourceAABB.min.y, sourceAABB.min.z },
		//	};

		//	outAABB.max = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		//	outAABB.min = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

		//	for (auto& p : pos) {
		//		Vector3 wPos = p.Transform(p, mWorld);
		//		outAABB.max = outAABB.max.Max(outAABB.max, wPos);
		//		outAABB.min = outAABB.min.Min(outAABB.min, wPos);
		//	}
		//}
	};

//class Frustum
	//{
	//public:
	//	/// @brief �R���X�g���N�^
	//	/// @param worldMatrix ���[���h�}�g���b�N�X
	//	/// @param fov FOV
	//	/// @param aspect �A�X�y�N�g��
	//	/// @param nearZ �j�A�N���b�v
	//	/// @param farZ �t�@�[�N���b�v
	//	explicit Frustum(const Matrix& worldMatrix, float fov, float aspect, float nearZ, float farZ)
	//	{
	//		CreateViewFrustum(fov, aspect, nearZ, farZ);
	//		UpdateViewFrustum(worldMatrix);
	//	}
	//
	//	/// @brief �R���X�g���N�^
	//	/// @param screenDepth �ő�̐[��
	//	/// @param viewMatrix �r���[�}�g���b�N�X
	//	/// @param projectionMatrix �v���W�F�N�V�����}�g���b�N�X
	//	explicit Frustum(float screenDepth, Matrix& viewMatrix, Matrix& projectionMatrix)
	//	{
	//		Matrix projMatrix = projectionMatrix;
	//		float zMinimum = -projMatrix._43 / projMatrix._33;
	//		float r = screenDepth / (screenDepth - zMinimum);
	//		projMatrix._33 = r;
	//		projMatrix._43 = -r * zMinimum;
	//
	//		Matrix matrix = XMMatrixMultiply(viewMatrix, projMatrix);
	//		float a, b, c, d;
	//
	//		// near
	//		a = matrix._14 + matrix._13;
	//		b = matrix._24 + matrix._23;
	//		c = matrix._34 + matrix._33;
	//		d = matrix._44 + matrix._43;
	//		m_planes[0] = XMVectorSet(a, b, c, d);
	//		m_planes[0] = XMPlaneNormalize(m_planes[0]);
	//
	//		// far
	//		a = matrix._14 - matrix._13;
	//		b = matrix._24 - matrix._23;
	//		c = matrix._34 - matrix._33;
	//		d = matrix._44 - matrix._43;
	//		m_planes[1] = XMVectorSet(a, b, c, d);
	//		m_planes[1] = XMPlaneNormalize(m_planes[1]);
	//
	//		// left
	//		a = matrix._14 + matrix._11;
	//		b = matrix._24 + matrix._21;
	//		c = matrix._34 + matrix._31;
	//		d = matrix._44 + matrix._41;
	//		m_planes[2] = XMVectorSet(a, b, c, d);
	//		m_planes[2] = XMPlaneNormalize(m_planes[2]);
	//
	//		// right
	//		a = matrix._14 - matrix._11;
	//		b = matrix._24 - matrix._21;
	//		c = matrix._34 - matrix._31;
	//		d = matrix._44 - matrix._41;
	//		m_planes[3] = XMVectorSet(a, b, c, d);
	//		m_planes[3] = XMPlaneNormalize(m_planes[3]);
	//
	//		// top
	//		a = matrix._14 - matrix._12;
	//		b = matrix._24 - matrix._22;
	//		c = matrix._34 - matrix._32;
	//		d = matrix._44 - matrix._42;
	//		m_planes[4] = XMVectorSet(a, b, c, d);
	//		m_planes[4] = XMPlaneNormalize(m_planes[4]);
	//
	//		// bottom
	//		a = matrix._14 + matrix._12;
	//		b = matrix._24 + matrix._22;
	//		c = matrix._34 + matrix._32;
	//		d = matrix._44 + matrix._42;
	//		m_planes[5] = XMVectorSet(a, b, c, d);
	//		m_planes[5] = XMPlaneNormalize(m_planes[5]);
	//	}
	//
	//	~Frustum() = default;
	//
	//public:
	//	bool CheckPoint(float x, float y, float z)
	//	{
	//		for (int i = 0; i < 6; i++)
	//		{
	//			float ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet(x, y, z, 1.0f)));
	//			if (ret < 0.0f)
	//				return false;
	//		}
	//
	//		return true;
	//	}
	//
	//	bool CheckCube(const Vector3& center, float size)
	//	{
	//		for (int i = 0; i < 6; i++)
	//		{
	//			float ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x - size), (center.y - size), (center.z - size), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x + size), (center.y - size), (center.z - size), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x - size), (center.y + size), (center.z - size), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x + size), (center.y + size), (center.z - size), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x - size), (center.y - size), (center.z + size), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x + size), (center.y - size), (center.z + size), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x - size), (center.y + size), (center.z + size), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x + size), (center.y + size), (center.z + size), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			return false;
	//		}
	//
	//		return true;
	//	}
	//
	//	bool CheckSphere(const Vector3& center, float radius)
	//	{
	//		for (int i = 0; i < 6; i++)
	//		{
	//			float ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet(center.x, center.y, center.z, 1.0f)));
	//			if (ret < -radius)
	//				return false;
	//		}
	//
	//		return true;
	//	}
	//
	//	bool CheckRectangle(const Vector3& center, const Vector3& size)
	//	{
	//		for (int i = 0; i < 6; i++)
	//		{
	//			float ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x - size.x), (center.y - size.y), (center.z - size.z), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x + size.x), (center.y - size.y), (center.z - size.z), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x - size.x), (center.y + size.y), (center.z - size.z), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x - size.x), (center.y - size.y), (center.z + size.z), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x + size.x), (center.y + size.y), (center.z - size.z), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x + size.x), (center.y - size.y), (center.z + size.z), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x - size.x), (center.y + size.y), (center.z + size.z), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((center.x + size.x), (center.y + size.y), (center.z + size.z), 1.0f)));
	//			if (ret >= 0.0f)
	//				continue;
	//
	//			return false;
	//		}
	//
	//		return true;
	//	}
	//
	//	bool CheckAABB(const AABB& aabb)
	//	{
	//		return CheckRectangle(aabb.center(), aabb.size());
	//	}
	//
	//private:
	//	// �v���W�F�N�V�����ϊ��p�����[�^���王���䐶��
	//	void CreateViewFrustum(float fov, float aspect, float nearZ, float farZ)
	//	{
	//		// 0:�O 1:��� 2:�� 3:�E 4:�� 5:��
	//		float fTan =
	//			tanf(XMConvertToRadians(fov) * 0.5f);
	//		float fTan2 = fTan * aspect;
	//		m_planes[0] = XMFLOAT4(0.0f, 0.0f, 1.0f, -nearZ);
	//		m_planes[1] = XMFLOAT4(0.0f, 0.0f, -1.0f, farZ);
	//		m_planes[2] = XMFLOAT4(1.0f, 0.0f, fTan2, 0.0f);
	//		m_planes[3] = XMFLOAT4(-1.0f, 0.0f, fTan2, 0.0f);
	//		m_planes[4] = XMFLOAT4(0.0f, -1.0f, fTan, 0.0f);
	//		m_planes[5] = XMFLOAT4(0.0f, 1.0f, fTan, 0.0f);
	//		// 0�`3�𐳋K��
	//		for (int i = 0; i < 6; ++i) {
	//			m_planes[i].Normalize();
	//		}
	//	}
	//
	//	// �J�����̃��[���h�}�g���b�N�X���王������ړ�
	//	void UpdateViewFrustum(const Matrix& worldMatrix)
	//	{
	//		// CalcWorldMatrix��m_mtxWorld���X�V�ς�O��
	//		XMMATRIX mW = XMLoadFloat4x4(&worldMatrix);
	//		mW = XMMatrixInverse(nullptr, mW);//�t�s��
	//		mW = XMMatrixTranspose(mW);//�]�u�s��
	//		// ���t�s��̓]�u�s������߂�̂�
	//		//   XMPlaneTransform�̎d�l!!
	//		for (int i = 0; i < 6; ++i) {
	//			m_planes[i] = XMPlaneTransform(m_planes[i], mW);
	//		}
	//	}
	//
	//private:
	//	// 0:�O 1:��� 2:�� 3:�E 4:�� 5:��
	//	Plane m_planes[6];
	//};



#endif // !_UTIL_MATHF_
