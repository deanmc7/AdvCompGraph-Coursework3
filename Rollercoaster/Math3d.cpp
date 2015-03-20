#include "Math3d.h"

// ----------------------------------------------------------------------------------------------------------------------------

float dot(const vec2 &u, const vec2 &v)
{
	return u.x * v.x + u.y * v.y;
}

float length(const vec2 &u)
{
	return sqrt(u.x * u.x + u.y * u.y);
}

float length2(const vec2 &u)
{
	return u.x * u.x + u.y * u.y;
}

vec2 mix(const vec2 &u, const vec2 &v, float a)
{
	return u * (1.0f - a) + v * a;
}

vec2 normalize(const vec2 &u)
{
	return u / sqrt(u.x * u.x + u.y * u.y);
}

vec2 reflect(const vec2 &i, const vec2 &n)
{
	return i - 2.0f * dot(n, i) * n;
}

vec2 refract(const vec2 &i, const vec2 &n, float eta)
{
	vec2 r;

	float ndoti = dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);

	if (k >= 0.0f)
	{
		r = eta * i - n * (eta * ndoti + sqrt(k));
	}

	return r;
}

vec2 rotate(const vec2 &u, float angle)
{
	angle = angle / 180.0f * (float)M_PI;

	float c = cos(angle), s = sin(angle);

	return vec2(u.x * c - u.y * s, u.x * s + u.y * c);
}

// ----------------------------------------------------------------------------------------------------------------------------

vec3 cross(const vec3 &u, const vec3 &v)
{
	return vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

float dot(const vec3 &u, const vec3 &v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

float length(const vec3 &u)
{
	return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

float length2(const vec3 &u)
{
	return u.x * u.x + u.y * u.y + u.z * u.z;
}

vec3 mix(const vec3 &u, const vec3 &v, float a)
{
	return u * (1.0f - a) + v * a;
}

vec3 normalize(const vec3 &u)
{
	return u / sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

vec3 reflect(const vec3 &i, const vec3 &n)
{
	return i - 2.0f * dot(n, i) * n;
}

vec3 refract(const vec3 &i, const vec3 &n, float eta)
{
	vec3 r;

	float ndoti = dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);

	if (k >= 0.0f)
	{
		r = eta * i - n * (eta * ndoti + sqrt(k));
	}

	return r;
}

vec3 rotate(const vec3 &u, float angle, const vec3 &v)
{
	return *(vec3*)&(rotate(angle, v) * vec4(u, 1.0f));
}

// ----------------------------------------------------------------------------------------------------------------------------

mat2x2::mat2x2()
{
	M[0] = 1.0f; M[2] = 0.0f;
	M[1] = 0.0f; M[3] = 1.0f;
}

mat2x2::~mat2x2()
{
}

mat2x2::mat2x2(const mat2x2 &Matrix)
{
	for (int i = 0; i < 4; i++)
	{
		M[i] = Matrix.M[i];
	}
}

mat2x2::mat2x2(const vec2 &col1, const vec2 &col2)
{
	M[0] = col1.x; M[2] = col2.x;
	M[1] = col1.y; M[3] = col2.y;
}

mat2x2::mat2x2(float c1r1, float c1r2, float c2r1, float c2r2)
{
	M[0] = c1r1; M[2] = c2r1;
	M[1] = c1r2; M[3] = c2r2;
}

mat2x2::mat2x2(const mat3x3 &Matrix)
{
	M[0] = Matrix.M[0]; M[2] = Matrix.M[3];
	M[1] = Matrix.M[1]; M[3] = Matrix.M[4];
}

mat2x2::mat2x2(const mat4x4 &Matrix)
{
	M[0] = Matrix.M[0]; M[2] = Matrix.M[4];
	M[1] = Matrix.M[1]; M[3] = Matrix.M[5];
}

mat2x2& mat2x2::operator = (const mat2x2 &Matrix)
{
	for (int i = 0; i < 4; i++)
	{
		M[i] = Matrix.M[i];
	}

	return *this;
}

float& mat2x2::operator [] (int i)
{
	return M[i];
}

float* mat2x2::operator & ()
{
	return (float*)this;
}

mat2x2 operator * (const mat2x2 &Matrix1, const mat2x2 &Matrix2)
{
	mat2x2 Matrix3;

	Matrix3.M[0] = Matrix1.M[0] * Matrix2.M[0] + Matrix1.M[2] * Matrix2.M[1];
	Matrix3.M[1] = Matrix1.M[1] * Matrix2.M[0] + Matrix1.M[3] * Matrix2.M[1];
	Matrix3.M[2] = Matrix1.M[0] * Matrix2.M[2] + Matrix1.M[2] * Matrix2.M[3];
	Matrix3.M[3] = Matrix1.M[1] * Matrix2.M[2] + Matrix1.M[3] * Matrix2.M[3];

	return Matrix3;
}

vec2 operator * (const mat2x2 &Matrix, const vec2 &u)
{
	vec2 v;

	v.x = Matrix.M[0] * u.x + Matrix.M[2] * u.y;
	v.y = Matrix.M[1] * u.x + Matrix.M[3] * u.y;

	return v;
}

// ----------------------------------------------------------------------------------------------------------------------------
//
// 0 2
// 1 3
//
// ----------------------------------------------------------------------------------------------------------------------------

mat2x2 inverse(const mat2x2 &Matrix)
{
	const float *m = Matrix.M;

	float det = m[0] * m[3] - m[2] * m[1];

	mat2x2 Inverse;

	Inverse.M[0] = m[3] / det;
	Inverse.M[1] = -m[1] / det;
	Inverse.M[2] = -m[2] / det;
	Inverse.M[3] = m[0] / det;

	return Inverse;
}

mat2x2 transpose(const mat2x2 &Matrix)
{
	mat2x2 Transpose;

	Transpose.M[0] = Matrix.M[0];
	Transpose.M[1] = Matrix.M[2];
	Transpose.M[2] = Matrix.M[1];
	Transpose.M[3] = Matrix.M[3];

	return Transpose;
}

// ----------------------------------------------------------------------------------------------------------------------------

mat3x3::mat3x3()
{
	M[0] = 1.0f; M[3] = 0.0f; M[6] = 0.0f;
	M[1] = 0.0f; M[4] = 1.0f; M[7] = 0.0f;
	M[2] = 0.0f; M[5] = 0.0f; M[8] = 1.0f;
}

mat3x3::~mat3x3()
{
}

mat3x3::mat3x3(const mat3x3 &Matrix)
{
	for (int i = 0; i < 9; i++)
	{
		M[i] = Matrix.M[i];
	}
}

mat3x3::mat3x3(const vec3 &col1, const vec3 &col2, const vec3 &col3)
{
	M[0] = col1.x; M[3] = col2.x; M[6] = col3.x;
	M[1] = col1.y; M[4] = col2.y; M[7] = col3.y;
	M[2] = col1.z; M[5] = col2.z; M[8] = col3.z;
}

mat3x3::mat3x3(float c1r1, float c1r2, float c1r3, float c2r1, float c2r2, float c2r3, float c3r1, float c3r2, float c3r3)
{
	M[0] = c1r1; M[3] = c2r1; M[6] = c3r1;
	M[1] = c1r2; M[4] = c2r2; M[7] = c3r2;
	M[2] = c1r3; M[5] = c2r3; M[8] = c3r3;
}

mat3x3::mat3x3(const mat2x2 &Matrix)
{
	M[0] = Matrix.M[0]; M[3] = Matrix.M[2]; M[6] = 0.0f;
	M[1] = Matrix.M[1]; M[4] = Matrix.M[3]; M[7] = 0.0f;
	M[2] = 0.0f; M[5] = 0.0f; M[8] = 1.0f;
}

mat3x3::mat3x3(const mat4x4 &Matrix)
{
	M[0] = Matrix.M[0]; M[3] = Matrix.M[4]; M[6] = Matrix.M[8];
	M[1] = Matrix.M[1]; M[4] = Matrix.M[5]; M[7] = Matrix.M[9];
	M[2] = Matrix.M[2]; M[5] = Matrix.M[6]; M[8] = Matrix.M[10];
}

mat3x3& mat3x3::operator = (const mat3x3 &Matrix)
{
	for (int i = 0; i < 9; i++)
	{
		M[i] = Matrix.M[i];
	}

	return *this;
}

float& mat3x3::operator [] (int i)
{
	return M[i];
}

float* mat3x3::operator & ()
{
	return (float*)this;
}

mat3x3 operator * (const mat3x3 &Matrix1, const mat3x3 &Matrix2)
{
	mat3x3 Matrix3;

	Matrix3.M[0] = Matrix1.M[0] * Matrix2.M[0] + Matrix1.M[3] * Matrix2.M[1] + Matrix1.M[6] * Matrix2.M[2];
	Matrix3.M[1] = Matrix1.M[1] * Matrix2.M[0] + Matrix1.M[4] * Matrix2.M[1] + Matrix1.M[7] * Matrix2.M[2];
	Matrix3.M[2] = Matrix1.M[2] * Matrix2.M[0] + Matrix1.M[5] * Matrix2.M[1] + Matrix1.M[8] * Matrix2.M[2];
	Matrix3.M[3] = Matrix1.M[0] * Matrix2.M[3] + Matrix1.M[3] * Matrix2.M[4] + Matrix1.M[6] * Matrix2.M[5];
	Matrix3.M[4] = Matrix1.M[1] * Matrix2.M[3] + Matrix1.M[4] * Matrix2.M[4] + Matrix1.M[7] * Matrix2.M[5];
	Matrix3.M[5] = Matrix1.M[2] * Matrix2.M[3] + Matrix1.M[5] * Matrix2.M[4] + Matrix1.M[8] * Matrix2.M[5];
	Matrix3.M[6] = Matrix1.M[0] * Matrix2.M[6] + Matrix1.M[3] * Matrix2.M[7] + Matrix1.M[6] * Matrix2.M[8];
	Matrix3.M[7] = Matrix1.M[1] * Matrix2.M[6] + Matrix1.M[4] * Matrix2.M[7] + Matrix1.M[7] * Matrix2.M[8];
	Matrix3.M[8] = Matrix1.M[2] * Matrix2.M[6] + Matrix1.M[5] * Matrix2.M[7] + Matrix1.M[8] * Matrix2.M[8];

	return Matrix3;
}

vec3 operator * (const mat3x3 &Matrix, const vec3 &u)
{
	vec3 v;

	v.x = Matrix.M[0] * u.x + Matrix.M[3] * u.y + Matrix.M[6] * u.z;
	v.y = Matrix.M[1] * u.x + Matrix.M[4] * u.y + Matrix.M[7] * u.z;
	v.z = Matrix.M[2] * u.x + Matrix.M[5] * u.y + Matrix.M[8] * u.z;

	return v;
}

// ----------------------------------------------------------------------------------------------------------------------------
//
// 0 3 6 | + - +
// 1 4 7 | - + -
// 2 5 8 | + - +
//
// ----------------------------------------------------------------------------------------------------------------------------

float det2x2sub(const float *m, int i0, int i1, int i2, int i3)
{
	return m[i0] * m[i3] - m[i2] * m[i1];
}

mat3x3 inverse(const mat3x3 &Matrix)
{
	const float *m = Matrix.M;

	float det = 0.0f;

	det += m[0] * det2x2sub(m, 4, 5, 7, 8);
	det -= m[3] * det2x2sub(m, 1, 2, 7, 8);
	det += m[6] * det2x2sub(m, 1, 2, 4, 5);

	mat3x3 Inverse;

	Inverse.M[0] = det2x2sub(m, 4, 5, 7, 8) / det;
	Inverse.M[1] = -det2x2sub(m, 1, 2, 7, 8) / det;
	Inverse.M[2] = det2x2sub(m, 1, 2, 4, 5) / det;
	Inverse.M[3] = -det2x2sub(m, 3, 5, 6, 8) / det;
	Inverse.M[4] = det2x2sub(m, 0, 2, 6, 8) / det;
	Inverse.M[5] = -det2x2sub(m, 0, 2, 3, 5) / det;
	Inverse.M[6] = det2x2sub(m, 3, 4, 6, 7) / det;
	Inverse.M[7] = -det2x2sub(m, 0, 1, 6, 7) / det;
	Inverse.M[8] = det2x2sub(m, 0, 1, 3, 4) / det;

	return Inverse;
}

mat3x3 transpose(const mat3x3 &Matrix)
{
	mat3x3 Transpose;

	Transpose.M[0] = Matrix.M[0];
	Transpose.M[1] = Matrix.M[3];
	Transpose.M[2] = Matrix.M[6];
	Transpose.M[3] = Matrix.M[1];
	Transpose.M[4] = Matrix.M[4];
	Transpose.M[5] = Matrix.M[7];
	Transpose.M[6] = Matrix.M[2];
	Transpose.M[7] = Matrix.M[5];
	Transpose.M[8] = Matrix.M[8];

	return Transpose;
}

// ----------------------------------------------------------------------------------------------------------------------------

mat4x4::mat4x4()
{
	M[0] = 1.0f; M[4] = 0.0f; M[8] = 0.0f; M[12] = 0.0f;
	M[1] = 0.0f; M[5] = 1.0f; M[9] = 0.0f; M[13] = 0.0f;
	M[2] = 0.0f; M[6] = 0.0f; M[10] = 1.0f; M[14] = 0.0f;
	M[3] = 0.0f; M[7] = 0.0f; M[11] = 0.0f; M[15] = 1.0f;
}

mat4x4::~mat4x4()
{
}

mat4x4::mat4x4(const mat4x4 &Matrix)
{
	for (int i = 0; i < 16; i++)
	{
		M[i] = Matrix.M[i];
	}
}

mat4x4::mat4x4(const vec4 &col1, const vec4 &col2, const vec4 &col3, const vec4 &col4)
{
	M[0] = col1.x; M[4] = col2.x; M[8] = col3.x; M[12] = col4.x;
	M[1] = col1.y; M[5] = col2.y; M[9] = col3.y; M[13] = col4.y;
	M[2] = col1.z; M[6] = col2.z; M[10] = col3.z; M[14] = col4.z;
	M[3] = col1.w; M[7] = col2.w; M[11] = col3.w; M[15] = col4.w;
}

mat4x4::mat4x4(float c1r1, float c1r2, float c1r3, float c1r4, float c2r1, float c2r2, float c2r3, float c2r4, float c3r1, float c3r2, float c3r3, float c3r4, float c4r1, float c4r2, float c4r3, float c4r4)
{
	M[0] = c1r1; M[4] = c2r1; M[8] = c3r1; M[12] = c4r1;
	M[1] = c1r2; M[5] = c2r2; M[9] = c3r2; M[13] = c4r2;
	M[2] = c1r3; M[6] = c2r3; M[10] = c3r3; M[14] = c4r3;
	M[3] = c1r4; M[7] = c2r4; M[11] = c3r4; M[15] = c4r4;
}

mat4x4::mat4x4(const mat2x2 &Matrix)
{
	M[0] = Matrix.M[0]; M[4] = Matrix.M[2]; M[8] = 0.0f; M[12] = 0.0f;
	M[1] = Matrix.M[1]; M[5] = Matrix.M[3]; M[9] = 0.0f; M[13] = 0.0f;
	M[2] = 0.0f; M[6] = 0.0f; M[10] = 1.0f; M[14] = 0.0f;
	M[3] = 0.0f; M[7] = 0.0f; M[11] = 0.0f; M[15] = 1.0f;
}

mat4x4::mat4x4(const mat3x3 &Matrix)
{
	M[0] = Matrix.M[0]; M[4] = Matrix.M[3]; M[8] = Matrix.M[6]; M[12] = 0.0f;
	M[1] = Matrix.M[1]; M[5] = Matrix.M[4]; M[9] = Matrix.M[7]; M[13] = 0.0f;
	M[2] = Matrix.M[2]; M[6] = Matrix.M[5]; M[10] = Matrix.M[8]; M[14] = 0.0f;
	M[3] = 0.0f; M[7] = 0.0f; M[11] = 0.0f; M[15] = 1.0f;
}

mat4x4& mat4x4::operator = (const mat4x4 &Matrix)
{
	for (int i = 0; i < 16; i++)
	{
		M[i] = Matrix.M[i];
	}

	return *this;
}

float& mat4x4::operator [] (int i)
{
	return M[i];
}

float* mat4x4::operator & ()
{
	return (float*)this;
}

mat4x4 operator * (const mat4x4 &Matrix1, const mat4x4 &Matrix2)
{
	mat4x4 Matrix3;

	Matrix3.M[0] = Matrix1.M[0] * Matrix2.M[0] + Matrix1.M[4] * Matrix2.M[1] + Matrix1.M[8] * Matrix2.M[2] + Matrix1.M[12] * Matrix2.M[3];
	Matrix3.M[1] = Matrix1.M[1] * Matrix2.M[0] + Matrix1.M[5] * Matrix2.M[1] + Matrix1.M[9] * Matrix2.M[2] + Matrix1.M[13] * Matrix2.M[3];
	Matrix3.M[2] = Matrix1.M[2] * Matrix2.M[0] + Matrix1.M[6] * Matrix2.M[1] + Matrix1.M[10] * Matrix2.M[2] + Matrix1.M[14] * Matrix2.M[3];
	Matrix3.M[3] = Matrix1.M[3] * Matrix2.M[0] + Matrix1.M[7] * Matrix2.M[1] + Matrix1.M[11] * Matrix2.M[2] + Matrix1.M[15] * Matrix2.M[3];
	Matrix3.M[4] = Matrix1.M[0] * Matrix2.M[4] + Matrix1.M[4] * Matrix2.M[5] + Matrix1.M[8] * Matrix2.M[6] + Matrix1.M[12] * Matrix2.M[7];
	Matrix3.M[5] = Matrix1.M[1] * Matrix2.M[4] + Matrix1.M[5] * Matrix2.M[5] + Matrix1.M[9] * Matrix2.M[6] + Matrix1.M[13] * Matrix2.M[7];
	Matrix3.M[6] = Matrix1.M[2] * Matrix2.M[4] + Matrix1.M[6] * Matrix2.M[5] + Matrix1.M[10] * Matrix2.M[6] + Matrix1.M[14] * Matrix2.M[7];
	Matrix3.M[7] = Matrix1.M[3] * Matrix2.M[4] + Matrix1.M[7] * Matrix2.M[5] + Matrix1.M[11] * Matrix2.M[6] + Matrix1.M[15] * Matrix2.M[7];
	Matrix3.M[8] = Matrix1.M[0] * Matrix2.M[8] + Matrix1.M[4] * Matrix2.M[9] + Matrix1.M[8] * Matrix2.M[10] + Matrix1.M[12] * Matrix2.M[11];
	Matrix3.M[9] = Matrix1.M[1] * Matrix2.M[8] + Matrix1.M[5] * Matrix2.M[9] + Matrix1.M[9] * Matrix2.M[10] + Matrix1.M[13] * Matrix2.M[11];
	Matrix3.M[10] = Matrix1.M[2] * Matrix2.M[8] + Matrix1.M[6] * Matrix2.M[9] + Matrix1.M[10] * Matrix2.M[10] + Matrix1.M[14] * Matrix2.M[11];
	Matrix3.M[11] = Matrix1.M[3] * Matrix2.M[8] + Matrix1.M[7] * Matrix2.M[9] + Matrix1.M[11] * Matrix2.M[10] + Matrix1.M[15] * Matrix2.M[11];
	Matrix3.M[12] = Matrix1.M[0] * Matrix2.M[12] + Matrix1.M[4] * Matrix2.M[13] + Matrix1.M[8] * Matrix2.M[14] + Matrix1.M[12] * Matrix2.M[15];
	Matrix3.M[13] = Matrix1.M[1] * Matrix2.M[12] + Matrix1.M[5] * Matrix2.M[13] + Matrix1.M[9] * Matrix2.M[14] + Matrix1.M[13] * Matrix2.M[15];
	Matrix3.M[14] = Matrix1.M[2] * Matrix2.M[12] + Matrix1.M[6] * Matrix2.M[13] + Matrix1.M[10] * Matrix2.M[14] + Matrix1.M[14] * Matrix2.M[15];
	Matrix3.M[15] = Matrix1.M[3] * Matrix2.M[12] + Matrix1.M[7] * Matrix2.M[13] + Matrix1.M[11] * Matrix2.M[14] + Matrix1.M[15] * Matrix2.M[15];

	return Matrix3;
}

vec4 operator * (const mat4x4 &Matrix, const vec4 &u)
{
	vec4 v;

	v.x = Matrix.M[0] * u.x + Matrix.M[4] * u.y + Matrix.M[8] * u.z + Matrix.M[12] * u.w;
	v.y = Matrix.M[1] * u.x + Matrix.M[5] * u.y + Matrix.M[9] * u.z + Matrix.M[13] * u.w;
	v.z = Matrix.M[2] * u.x + Matrix.M[6] * u.y + Matrix.M[10] * u.z + Matrix.M[14] * u.w;
	v.w = Matrix.M[3] * u.x + Matrix.M[7] * u.y + Matrix.M[11] * u.z + Matrix.M[15] * u.w;

	return v;
}

// ----------------------------------------------------------------------------------------------------------------------------

mat4x4 BiasMatrix = mat4x4(0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f);
mat4x4 BiasMatrixInverse = mat4x4(2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, -1.0f, -1.0f, -1.0f, 1.0f);

// ----------------------------------------------------------------------------------------------------------------------------
//
// 0 4  8 12 | + - + -
// 1 5  9 13 | - + - +
// 2 6 10 14 | + - + -
// 3 7 11 15 | - + - +
//
// ----------------------------------------------------------------------------------------------------------------------------

float det3x3sub(const float *m, int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
{
	float det = 0.0f;

	det += m[i0] * det2x2sub(m, i4, i5, i7, i8);
	det -= m[i3] * det2x2sub(m, i1, i2, i7, i8);
	det += m[i6] * det2x2sub(m, i1, i2, i4, i5);

	return det;
}

mat4x4 inverse(const mat4x4 &Matrix)
{
	const float *m = Matrix.M;

	float det = 0.0f;

	det += m[0] * det3x3sub(m, 5, 6, 7, 9, 10, 11, 13, 14, 15);
	det -= m[4] * det3x3sub(m, 1, 2, 3, 9, 10, 11, 13, 14, 15);
	det += m[8] * det3x3sub(m, 1, 2, 3, 5, 6, 7, 13, 14, 15);
	det -= m[12] * det3x3sub(m, 1, 2, 3, 5, 6, 7, 9, 10, 11);

	mat4x4 Inverse;

	Inverse.M[0] = det3x3sub(m, 5, 6, 7, 9, 10, 11, 13, 14, 15) / det;
	Inverse.M[1] = -det3x3sub(m, 1, 2, 3, 9, 10, 11, 13, 14, 15) / det;
	Inverse.M[2] = det3x3sub(m, 1, 2, 3, 5, 6, 7, 13, 14, 15) / det;
	Inverse.M[3] = -det3x3sub(m, 1, 2, 3, 5, 6, 7, 9, 10, 11) / det;
	Inverse.M[4] = -det3x3sub(m, 4, 6, 7, 8, 10, 11, 12, 14, 15) / det;
	Inverse.M[5] = det3x3sub(m, 0, 2, 3, 8, 10, 11, 12, 14, 15) / det;
	Inverse.M[6] = -det3x3sub(m, 0, 2, 3, 4, 6, 7, 12, 14, 15) / det;
	Inverse.M[7] = det3x3sub(m, 0, 2, 3, 4, 6, 7, 8, 10, 11) / det;
	Inverse.M[8] = det3x3sub(m, 4, 5, 7, 8, 9, 11, 12, 13, 15) / det;
	Inverse.M[9] = -det3x3sub(m, 0, 1, 3, 8, 9, 11, 12, 13, 15) / det;
	Inverse.M[10] = det3x3sub(m, 0, 1, 3, 4, 5, 7, 12, 13, 15) / det;
	Inverse.M[11] = -det3x3sub(m, 0, 1, 3, 4, 5, 7, 8, 9, 11) / det;
	Inverse.M[12] = -det3x3sub(m, 4, 5, 6, 8, 9, 10, 12, 13, 14) / det;
	Inverse.M[13] = det3x3sub(m, 0, 1, 2, 8, 9, 10, 12, 13, 14) / det;
	Inverse.M[14] = -det3x3sub(m, 0, 1, 2, 4, 5, 6, 12, 13, 14) / det;
	Inverse.M[15] = det3x3sub(m, 0, 1, 2, 4, 5, 6, 8, 9, 10) / det;

	return Inverse;
}

mat4x4 look(const vec3 &eye, const vec3 &center, const vec3 &up)
{
	vec3 Z = normalize(eye - center);
	vec3 X = normalize(cross(up, Z));
	vec3 Y = cross(Z, X);

	mat4x4 View;

	View.M[0] = X.x;
	View.M[1] = Y.x;
	View.M[2] = Z.x;
	View.M[4] = X.y;
	View.M[5] = Y.y;
	View.M[6] = Z.y;
	View.M[8] = X.z;
	View.M[9] = Y.z;
	View.M[10] = Z.z;
	View.M[12] = -dot(X, eye);
	View.M[13] = -dot(Y, eye);
	View.M[14] = -dot(Z, eye);

	return View;
}

mat4x4 ortho(float left, float right, float bottom, float top, float n, float f)
{
	mat4x4 Ortho;

	Ortho.M[0] = 2.0f / (right - left);
	Ortho.M[5] = 2.0f / (top - bottom);
	Ortho.M[10] = -2.0f / (f - n);
	Ortho.M[12] = -(right + left) / (right - left);
	Ortho.M[13] = -(top + bottom) / (top - bottom);
	Ortho.M[14] = -(f + n) / (f - n);

	return Ortho;
}

mat4x4 perspective(float fovy, float aspect, float n, float f)
{
	mat4x4 Perspective;

	float coty = 1.0f / tan(fovy * (float)M_PI / 360.0f);

	Perspective.M[0] = coty / aspect;
	Perspective.M[5] = coty;
	Perspective.M[10] = (n + f) / (n - f);
	Perspective.M[11] = -1.0f;
	Perspective.M[14] = 2.0f * n * f / (n - f);
	Perspective.M[15] = 0.0f;

	return Perspective;
}

mat4x4 rotate(float angle, const vec3 &u)
{
	mat4x4 Rotate;

	angle = angle / 180.0f * (float)M_PI;

	vec3 v = normalize(u);

	float c = 1.0f - cos(angle), s = sin(angle);

	Rotate.M[0] = 1.0f + c * (v.x * v.x - 1.0f);
	Rotate.M[1] = c * v.x * v.y + v.z * s;
	Rotate.M[2] = c * v.x * v.z - v.y * s;
	Rotate.M[4] = c * v.x * v.y - v.z * s;
	Rotate.M[5] = 1.0f + c * (v.y * v.y - 1.0f);
	Rotate.M[6] = c * v.y * v.z + v.x * s;
	Rotate.M[8] = c * v.x * v.z + v.y * s;
	Rotate.M[9] = c * v.y * v.z - v.x * s;
	Rotate.M[10] = 1.0f + c * (v.z * v.z - 1.0f);

	return Rotate;
}

mat4x4 scale(float x, float y, float z)
{
	mat4x4 Scale;

	Scale.M[0] = x;
	Scale.M[5] = y;
	Scale.M[10] = z;

	return Scale;
}

mat4x4 translate(float x, float y, float z)
{
	mat4x4 Translate;

	Translate.M[12] = x;
	Translate.M[13] = y;
	Translate.M[14] = z;

	return Translate;
}

mat4x4 transpose(const mat4x4 &Matrix)
{
	mat4x4 Transpose;

	Transpose.M[0] = Matrix.M[0];
	Transpose.M[1] = Matrix.M[4];
	Transpose.M[2] = Matrix.M[8];
	Transpose.M[3] = Matrix.M[12];
	Transpose.M[4] = Matrix.M[1];
	Transpose.M[5] = Matrix.M[5];
	Transpose.M[6] = Matrix.M[9];
	Transpose.M[7] = Matrix.M[13];
	Transpose.M[8] = Matrix.M[2];
	Transpose.M[9] = Matrix.M[6];
	Transpose.M[10] = Matrix.M[10];
	Transpose.M[11] = Matrix.M[14];
	Transpose.M[12] = Matrix.M[3];
	Transpose.M[13] = Matrix.M[7];
	Transpose.M[14] = Matrix.M[11];
	Transpose.M[15] = Matrix.M[15];

	return Transpose;
}



// Math3d.c
// Implementation of non-inlined functions in the Math3D Library


// These are pretty portable
#include <math.h>
#include "math3d.h"


////////////////////////////////////////////////////////////
// LoadIdentity
// For 3x3 and 4x4 float and double matrices.
// 3x3 float
void m3dLoadIdentity33(M3DMatrix33f m)
{
	// Don't be fooled, this is still column major
	static M3DMatrix33f	identity = { 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f };

	memcpy(m, identity, sizeof(M3DMatrix33f));
}

// 3x3 double
void m3dLoadIdentity33(M3DMatrix33d m)
{
	// Don't be fooled, this is still column major
	static M3DMatrix33d	identity = { 1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0 };

	memcpy(m, identity, sizeof(M3DMatrix33d));
}

// 4x4 float
void m3dLoadIdentity44(M3DMatrix44f m)
{
	// Don't be fooled, this is still column major
	static M3DMatrix44f	identity = { 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	memcpy(m, identity, sizeof(M3DMatrix44f));
}

// 4x4 double
void m3dLoadIdentity44(M3DMatrix44d m)
{
	static M3DMatrix44d	identity = { 1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0 };

	memcpy(m, identity, sizeof(M3DMatrix44d));
}


////////////////////////////////////////////////////////////////////////
// Return the square of the distance between two points
// Should these be inlined...?
float m3dGetDistanceSquared(const M3DVector3f u, const M3DVector3f v)
{
	float x = u[0] - v[0];
	x = x*x;

	float y = u[1] - v[1];
	y = y*y;

	float z = u[2] - v[2];
	z = z*z;

	return (x + y + z);
}

// Ditto above, but for doubles
double m3dGetDistanceSquared(const M3DVector3d u, const M3DVector3d v)
{
	double x = u[0] - v[0];
	x = x*x;

	double y = u[1] - v[1];
	y = y*y;

	double z = u[2] - v[2];
	z = z*z;

	return (x + y + z);
}

#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  product[(col<<2)+row]

///////////////////////////////////////////////////////////////////////////////
// Multiply two 4x4 matricies
void m3dMatrixMultiply44(M3DMatrix44f product, const M3DMatrix44f a, const M3DMatrix44f b)
{
	for (int i = 0; i < 4; i++) {
		float ai0 = A(i, 0), ai1 = A(i, 1), ai2 = A(i, 2), ai3 = A(i, 3);
		P(i, 0) = ai0 * B(0, 0) + ai1 * B(1, 0) + ai2 * B(2, 0) + ai3 * B(3, 0);
		P(i, 1) = ai0 * B(0, 1) + ai1 * B(1, 1) + ai2 * B(2, 1) + ai3 * B(3, 1);
		P(i, 2) = ai0 * B(0, 2) + ai1 * B(1, 2) + ai2 * B(2, 2) + ai3 * B(3, 2);
		P(i, 3) = ai0 * B(0, 3) + ai1 * B(1, 3) + ai2 * B(2, 3) + ai3 * B(3, 3);
	}
}

// Ditto above, but for doubles
void m3dMatrixMultiply(M3DMatrix44d product, const M3DMatrix44d a, const M3DMatrix44d b)
{
	for (int i = 0; i < 4; i++) {
		double ai0 = A(i, 0), ai1 = A(i, 1), ai2 = A(i, 2), ai3 = A(i, 3);
		P(i, 0) = ai0 * B(0, 0) + ai1 * B(1, 0) + ai2 * B(2, 0) + ai3 * B(3, 0);
		P(i, 1) = ai0 * B(0, 1) + ai1 * B(1, 1) + ai2 * B(2, 1) + ai3 * B(3, 1);
		P(i, 2) = ai0 * B(0, 2) + ai1 * B(1, 2) + ai2 * B(2, 2) + ai3 * B(3, 2);
		P(i, 3) = ai0 * B(0, 3) + ai1 * B(1, 3) + ai2 * B(2, 3) + ai3 * B(3, 3);
	}
}
#undef A
#undef B
#undef P


#define A33(row,col)  a[(col*3)+row]
#define B33(row,col)  b[(col*3)+row]
#define P33(row,col)  product[(col*3)+row]

///////////////////////////////////////////////////////////////////////////////
// Multiply two 3x3 matricies
void m3dMatrixMultiply33(M3DMatrix33f product, const M3DMatrix33f a, const M3DMatrix33f b)
{
	for (int i = 0; i < 3; i++) {
		float ai0 = A33(i, 0), ai1 = A33(i, 1), ai2 = A33(i, 2);
		P33(i, 0) = ai0 * B33(0, 0) + ai1 * B33(1, 0) + ai2 * B33(2, 0);
		P33(i, 1) = ai0 * B33(0, 1) + ai1 * B33(1, 1) + ai2 * B33(2, 1);
		P33(i, 2) = ai0 * B33(0, 2) + ai1 * B33(1, 2) + ai2 * B33(2, 2);
	}
}

// Ditto above, but for doubles
void m3dMatrixMultiply44(M3DMatrix33d product, const M3DMatrix33d a, const M3DMatrix33d b)
{
	for (int i = 0; i < 3; i++) {
		double ai0 = A33(i, 0), ai1 = A33(i, 1), ai2 = A33(i, 2);
		P33(i, 0) = ai0 * B33(0, 0) + ai1 * B33(1, 0) + ai2 * B33(2, 0);
		P33(i, 1) = ai0 * B33(0, 1) + ai1 * B33(1, 1) + ai2 * B33(2, 1);
		P33(i, 2) = ai0 * B33(0, 2) + ai1 * B33(1, 2) + ai2 * B33(2, 2);
	}
}

#undef A33
#undef B33
#undef P33

#define M33(row,col)  m[col*3+row]

///////////////////////////////////////////////////////////////////////////////
// Creates a 3x3 rotation matrix, takes radians NOT degrees
void m3dRotationMatrix33(M3DMatrix33f m, float angle, float x, float y, float z)
{

	float mag, s, c;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = float(sin(angle));
	c = float(cos(angle));

	mag = float(sqrt(x*x + y*y + z*z));

	// Identity matrix
	if (mag == 0.0f) {
		m3dLoadIdentity33(m);
		return;
	}

	// Rotation matrix is normalized
	x /= mag;
	y /= mag;
	z /= mag;



	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0f - c;

	M33(0, 0) = (one_c * xx) + c;
	M33(0, 1) = (one_c * xy) - zs;
	M33(0, 2) = (one_c * zx) + ys;

	M33(1, 0) = (one_c * xy) + zs;
	M33(1, 1) = (one_c * yy) + c;
	M33(1, 2) = (one_c * yz) - xs;

	M33(2, 0) = (one_c * zx) - ys;
	M33(2, 1) = (one_c * yz) + xs;
	M33(2, 2) = (one_c * zz) + c;
}

#undef M33

///////////////////////////////////////////////////////////////////////////////
// Creates a 4x4 rotation matrix, takes radians NOT degrees
void m3dRotationMatrix44(M3DMatrix44f m, float angle, float x, float y, float z)
{
	float mag, s, c;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = float(sin(angle));
	c = float(cos(angle));

	mag = float(sqrt(x*x + y*y + z*z));

	// Identity matrix
	if (mag == 0.0f) {
		m3dLoadIdentity44(m);
		return;
	}

	// Rotation matrix is normalized
	x /= mag;
	y /= mag;
	z /= mag;

#define M(row,col)  m[col*4+row]

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0f - c;

	M(0, 0) = (one_c * xx) + c;
	M(0, 1) = (one_c * xy) - zs;
	M(0, 2) = (one_c * zx) + ys;
	M(0, 3) = 0.0f;

	M(1, 0) = (one_c * xy) + zs;
	M(1, 1) = (one_c * yy) + c;
	M(1, 2) = (one_c * yz) - xs;
	M(1, 3) = 0.0f;

	M(2, 0) = (one_c * zx) - ys;
	M(2, 1) = (one_c * yz) + xs;
	M(2, 2) = (one_c * zz) + c;
	M(2, 3) = 0.0f;

	M(3, 0) = 0.0f;
	M(3, 1) = 0.0f;
	M(3, 2) = 0.0f;
	M(3, 3) = 1.0f;

#undef M
}



///////////////////////////////////////////////////////////////////////////////
// Ditto above, but for doubles
void m3dRotationMatrix33(M3DMatrix33d m, double angle, double x, double y, double z)
{
	double mag, s, c;
	double xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = sin(angle);
	c = cos(angle);

	mag = sqrt(x*x + y*y + z*z);

	// Identity matrix
	if (mag == 0.0) {
		m3dLoadIdentity33(m);
		return;
	}

	// Rotation matrix is normalized
	x /= mag;
	y /= mag;
	z /= mag;

#define M(row,col)  m[col*3+row]

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0 - c;

	M(0, 0) = (one_c * xx) + c;
	M(0, 1) = (one_c * xy) - zs;
	M(0, 2) = (one_c * zx) + ys;

	M(1, 0) = (one_c * xy) + zs;
	M(1, 1) = (one_c * yy) + c;
	M(1, 2) = (one_c * yz) - xs;

	M(2, 0) = (one_c * zx) - ys;
	M(2, 1) = (one_c * yz) + xs;
	M(2, 2) = (one_c * zz) + c;

#undef M
}


///////////////////////////////////////////////////////////////////////////////
// Creates a 4x4 rotation matrix, takes radians NOT degrees
void m3dRotationMatrix44(M3DMatrix44d m, double angle, double x, double y, double z)
{
	double mag, s, c;
	double xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = sin(angle);
	c = cos(angle);

	mag = sqrt(x*x + y*y + z*z);

	// Identity matrix
	if (mag == 0.0) {
		m3dLoadIdentity44(m);
		return;
	}

	// Rotation matrix is normalized
	x /= mag;
	y /= mag;
	z /= mag;

#define M(row,col)  m[col*4+row]

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0f - c;

	M(0, 0) = (one_c * xx) + c;
	M(0, 1) = (one_c * xy) - zs;
	M(0, 2) = (one_c * zx) + ys;
	M(0, 3) = 0.0;

	M(1, 0) = (one_c * xy) + zs;
	M(1, 1) = (one_c * yy) + c;
	M(1, 2) = (one_c * yz) - xs;
	M(1, 3) = 0.0;

	M(2, 0) = (one_c * zx) - ys;
	M(2, 1) = (one_c * yz) + xs;
	M(2, 2) = (one_c * zz) + c;
	M(2, 3) = 0.0;

	M(3, 0) = 0.0;
	M(3, 1) = 0.0;
	M(3, 2) = 0.0;
	M(3, 3) = 1.0;

#undef M
}

// Lifted from Mesa
/*
* Compute inverse of 4x4 transformation matrix.
* Code contributed by Jacques Leroy jle@star.be
* Return GL_TRUE for success, GL_FALSE for failure (singular matrix)
*/
bool m3dInvertMatrix44(M3DMatrix44f dst, const M3DMatrix44f src)
{
#define SWAP_ROWS(a, b) { float *_tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c) (m)[(c)*4+(r)]

	float wtmp[4][8];
	float m0, m1, m2, m3, s;
	float *r0, *r1, *r2, *r3;

	r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

	r0[0] = MAT(src, 0, 0), r0[1] = MAT(src, 0, 1),
		r0[2] = MAT(src, 0, 2), r0[3] = MAT(src, 0, 3),
		r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,

		r1[0] = MAT(src, 1, 0), r1[1] = MAT(src, 1, 1),
		r1[2] = MAT(src, 1, 2), r1[3] = MAT(src, 1, 3),
		r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,

		r2[0] = MAT(src, 2, 0), r2[1] = MAT(src, 2, 1),
		r2[2] = MAT(src, 2, 2), r2[3] = MAT(src, 2, 3),
		r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,

		r3[0] = MAT(src, 3, 0), r3[1] = MAT(src, 3, 1),
		r3[2] = MAT(src, 3, 2), r3[3] = MAT(src, 3, 3),
		r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

	/* choose pivot - or die */
	if (fabs(r3[0])>fabs(r2[0])) SWAP_ROWS(r3, r2);
	if (fabs(r2[0])>fabs(r1[0])) SWAP_ROWS(r2, r1);
	if (fabs(r1[0])>fabs(r0[0])) SWAP_ROWS(r1, r0);
	if (0.0 == r0[0])  return false;

	/* eliminate first variable     */
	m1 = r1[0] / r0[0]; m2 = r2[0] / r0[0]; m3 = r3[0] / r0[0];
	s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
	s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
	s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
	s = r0[4];
	if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r0[5];
	if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r0[6];
	if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r0[7];
	if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

	/* choose pivot - or die */
	if (fabs(r3[1])>fabs(r2[1])) SWAP_ROWS(r3, r2);
	if (fabs(r2[1])>fabs(r1[1])) SWAP_ROWS(r2, r1);
	if (0.0 == r1[1])  return false;

	/* eliminate second variable */
	m2 = r2[1] / r1[1]; m3 = r3[1] / r1[1];
	r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
	s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

	/* choose pivot - or die */
	if (fabs(r3[2])>fabs(r2[2])) SWAP_ROWS(r3, r2);
	if (0.0 == r2[2])  return false;

	/* eliminate third variable */
	m3 = r3[2] / r2[2];
	r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
		r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
		r3[7] -= m3 * r2[7];

	/* last check */
	if (0.0 == r3[3]) return false;

	s = 1.0f / r3[3];              /* now back substitute row 3 */
	r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

	m2 = r2[3];                 /* now back substitute row 2 */
	s = 1.0f / r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
		r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3];
	r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
		r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
	m0 = r0[3];
	r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
		r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

	m1 = r1[2];                 /* now back substitute row 1 */
	s = 1.0f / r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
		r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2];
	r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
		r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

	m0 = r0[1];                 /* now back substitute row 0 */
	s = 1.0f / r0[0];
	r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
		r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

	MAT(dst, 0, 0) = r0[4]; MAT(dst, 0, 1) = r0[5],
		MAT(dst, 0, 2) = r0[6]; MAT(dst, 0, 3) = r0[7],
		MAT(dst, 1, 0) = r1[4]; MAT(dst, 1, 1) = r1[5],
		MAT(dst, 1, 2) = r1[6]; MAT(dst, 1, 3) = r1[7],
		MAT(dst, 2, 0) = r2[4]; MAT(dst, 2, 1) = r2[5],
		MAT(dst, 2, 2) = r2[6]; MAT(dst, 2, 3) = r2[7],
		MAT(dst, 3, 0) = r3[4]; MAT(dst, 3, 1) = r3[5],
		MAT(dst, 3, 2) = r3[6]; MAT(dst, 3, 3) = r3[7];

	return true;

#undef MAT
#undef SWAP_ROWS
}


// Ditto above, but for doubles
bool m3dInvertMatrix44(M3DMatrix44d dst, const M3DMatrix44d src)
{
#define SWAP_ROWS(a, b) { double *_tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c) (m)[(c)*4+(r)]

	double wtmp[4][8];
	double m0, m1, m2, m3, s;
	double *r0, *r1, *r2, *r3;

	r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

	r0[0] = MAT(src, 0, 0), r0[1] = MAT(src, 0, 1),
		r0[2] = MAT(src, 0, 2), r0[3] = MAT(src, 0, 3),
		r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,

		r1[0] = MAT(src, 1, 0), r1[1] = MAT(src, 1, 1),
		r1[2] = MAT(src, 1, 2), r1[3] = MAT(src, 1, 3),
		r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,

		r2[0] = MAT(src, 2, 0), r2[1] = MAT(src, 2, 1),
		r2[2] = MAT(src, 2, 2), r2[3] = MAT(src, 2, 3),
		r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,

		r3[0] = MAT(src, 3, 0), r3[1] = MAT(src, 3, 1),
		r3[2] = MAT(src, 3, 2), r3[3] = MAT(src, 3, 3),
		r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

	// choose pivot - or die 
	if (fabs(r3[0])>fabs(r2[0])) SWAP_ROWS(r3, r2);
	if (fabs(r2[0])>fabs(r1[0])) SWAP_ROWS(r2, r1);
	if (fabs(r1[0])>fabs(r0[0])) SWAP_ROWS(r1, r0);
	if (0.0 == r0[0])  return false;

	// eliminate first variable     
	m1 = r1[0] / r0[0]; m2 = r2[0] / r0[0]; m3 = r3[0] / r0[0];
	s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
	s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
	s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
	s = r0[4];
	if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r0[5];
	if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r0[6];
	if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r0[7];
	if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

	// choose pivot - or die 
	if (fabs(r3[1])>fabs(r2[1])) SWAP_ROWS(r3, r2);
	if (fabs(r2[1])>fabs(r1[1])) SWAP_ROWS(r2, r1);
	if (0.0 == r1[1])  return false;

	// eliminate second variable 
	m2 = r2[1] / r1[1]; m3 = r3[1] / r1[1];
	r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
	s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

	// choose pivot - or die 
	if (fabs(r3[2])>fabs(r2[2])) SWAP_ROWS(r3, r2);
	if (0.0 == r2[2])  return false;

	// eliminate third variable 
	m3 = r3[2] / r2[2];
	r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
		r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
		r3[7] -= m3 * r2[7];

	// last check 
	if (0.0 == r3[3]) return false;

	s = 1.0f / r3[3];              // now back substitute row 3 
	r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

	m2 = r2[3];                 // now back substitute row 2 
	s = 1.0f / r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
		r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3];
	r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
		r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
	m0 = r0[3];
	r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
		r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

	m1 = r1[2];                 // now back substitute row 1 
	s = 1.0f / r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
		r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2];
	r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
		r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

	m0 = r0[1];                 // now back substitute row 0 
	s = 1.0f / r0[0];
	r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
		r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

	MAT(dst, 0, 0) = r0[4]; MAT(dst, 0, 1) = r0[5],
		MAT(dst, 0, 2) = r0[6]; MAT(dst, 0, 3) = r0[7],
		MAT(dst, 1, 0) = r1[4]; MAT(dst, 1, 1) = r1[5],
		MAT(dst, 1, 2) = r1[6]; MAT(dst, 1, 3) = r1[7],
		MAT(dst, 2, 0) = r2[4]; MAT(dst, 2, 1) = r2[5],
		MAT(dst, 2, 2) = r2[6]; MAT(dst, 2, 3) = r2[7],
		MAT(dst, 3, 0) = r3[4]; MAT(dst, 3, 1) = r3[5],
		MAT(dst, 3, 2) = r3[6]; MAT(dst, 3, 3) = r3[7];

	return true;

#undef MAT
#undef SWAP_ROWS

	return true;
}



///////////////////////////////////////////////////////////////////////////////////////
// Get Window coordinates, discard Z...
void m3dProjectXY(const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn, M3DVector2f vPointOut)
{
	M3DVector4f vBack, vForth;

	memcpy(vBack, vPointIn, sizeof(float) * 3);
	vBack[3] = 1.0f;

	m3dTransformVector4(vForth, vBack, mModelView);
	m3dTransformVector4(vBack, vForth, mProjection);

	if (!m3dCloseEnough(vBack[3], 0.0f, 0.000001f)) {
		float div = 1.0f / vBack[3];
		vBack[0] *= div;
		vBack[1] *= div;
	}


	vPointOut[0] = vBack[0] * 0.5f + 0.5f;
	vPointOut[1] = vBack[1] * 0.5f + 0.5f;

	/* Map x,y to viewport */
	vPointOut[0] = (vPointOut[0] * iViewPort[2]) + iViewPort[0];
	vPointOut[1] = (vPointOut[1] * iViewPort[3]) + iViewPort[1];
}

///////////////////////////////////////////////////////////////////////////////////////
// Get window coordinates, we also want Z....
void m3dProjectXYZ(const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn, M3DVector3f vPointOut)
{
	M3DVector4f vBack, vForth;

	memcpy(vBack, vPointIn, sizeof(float) * 3);
	vBack[3] = 1.0f;

	m3dTransformVector4(vForth, vBack, mModelView);
	m3dTransformVector4(vBack, vForth, mProjection);

	if (!m3dCloseEnough(vBack[3], 0.0f, 0.000001f)) {
		float div = 1.0f / vBack[3];
		vBack[0] *= div;
		vBack[1] *= div;
		vBack[2] *= div;
	}

	vPointOut[0] = vBack[0] * 0.5f + 0.5f;
	vPointOut[1] = vBack[1] * 0.5f + 0.5f;
	vPointOut[2] = vBack[2] * 0.5f + 0.5f;

	/* Map x,y to viewport */
	vPointOut[0] = (vPointOut[0] * iViewPort[2]) + iViewPort[0];
	vPointOut[1] = (vPointOut[1] * iViewPort[3]) + iViewPort[1];
}



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Misc. Utilities
///////////////////////////////////////////////////////////////////////////////
// Calculates the normal of a triangle specified by the three points
// p1, p2, and p3. Each pointer points to an array of three floats. The
// triangle is assumed to be wound counter clockwise. 
void m3dFindNormal(M3DVector3f result, const M3DVector3f point1, const M3DVector3f point2,
	const M3DVector3f point3)
{
	M3DVector3f v1, v2;		// Temporary vectors

	// Calculate two vectors from the three points. Assumes counter clockwise
	// winding!
	v1[0] = point1[0] - point2[0];
	v1[1] = point1[1] - point2[1];
	v1[2] = point1[2] - point2[2];

	v2[0] = point2[0] - point3[0];
	v2[1] = point2[1] - point3[1];
	v2[2] = point2[2] - point3[2];

	// Take the cross product of the two vectors to get
	// the normal vector.
	m3dCrossProduct(result, v1, v2);
}



// Ditto above, but for doubles
void m3dFindNormal(M3DVector3d result, const M3DVector3d point1, const M3DVector3d point2,
	const M3DVector3d point3)
{
	M3DVector3d v1, v2;		// Temporary vectors

	// Calculate two vectors from the three points. Assumes counter clockwise
	// winding!
	v1[0] = point1[0] - point2[0];
	v1[1] = point1[1] - point2[1];
	v1[2] = point1[2] - point2[2];

	v2[0] = point2[0] - point3[0];
	v2[1] = point2[1] - point3[1];
	v2[2] = point2[2] - point3[2];

	// Take the cross product of the two vectors to get
	// the normal vector.
	m3dCrossProduct(result, v1, v2);
}



/////////////////////////////////////////////////////////////////////////////////////////
// Calculate the plane equation of the plane that the three specified points lay in. The
// points are given in clockwise winding order, with normal pointing out of clockwise face
// planeEq contains the A,B,C, and D of the plane equation coefficients
void m3dGetPlaneEquation(M3DVector4f planeEq, const M3DVector3f p1, const M3DVector3f p2, const M3DVector3f p3)
{
	// Get two vectors... do the cross product
	M3DVector3f v1, v2;

	// V1 = p3 - p1
	v1[0] = p3[0] - p1[0];
	v1[1] = p3[1] - p1[1];
	v1[2] = p3[2] - p1[2];

	// V2 = P2 - p1
	v2[0] = p2[0] - p1[0];
	v2[1] = p2[1] - p1[1];
	v2[2] = p2[2] - p1[2];

	// Unit normal to plane - Not sure which is the best way here
	m3dCrossProduct(planeEq, v1, v2);
	m3dNormalizeVector(planeEq);
	// Back substitute to get D
	planeEq[3] = -(planeEq[0] * p3[0] + planeEq[1] * p3[1] + planeEq[2] * p3[2]);
}


// Ditto above, but for doubles
void m3dGetPlaneEquation(M3DVector4d planeEq, const M3DVector3d p1, const M3DVector3d p2, const M3DVector3d p3)
{
	// Get two vectors... do the cross product
	M3DVector3d v1, v2;

	// V1 = p3 - p1
	v1[0] = p3[0] - p1[0];
	v1[1] = p3[1] - p1[1];
	v1[2] = p3[2] - p1[2];

	// V2 = P2 - p1
	v2[0] = p2[0] - p1[0];
	v2[1] = p2[1] - p1[1];
	v2[2] = p2[2] - p1[2];

	// Unit normal to plane - Not sure which is the best way here
	m3dCrossProduct(planeEq, v1, v2);
	m3dNormalizeVector(planeEq);
	// Back substitute to get D
	planeEq[3] = -(planeEq[0] * p3[0] + planeEq[1] * p3[1] + planeEq[2] * p3[2]);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// This function does a three dimensional Catmull-Rom curve interpolation. Pass four points, and a
// floating point number between 0.0 and 1.0. The curve is interpolated between the middle two points.
// Coded by RSW
// http://www.mvps.org/directx/articles/catmull/
void m3dCatmullRom3(M3DVector3f vOut, M3DVector3f vP0, M3DVector3f vP1, M3DVector3f vP2, M3DVector3f vP3, float t)
{
	// Unrolled loop to speed things up a little bit...
	float t2 = t * t;
	float t3 = t2 * t;

	// X    
	vOut[0] = 0.5f * ((2.0f * vP1[0]) +
		(-vP0[0] + vP2[0]) * t +
		(2.0f * vP0[0] - 5.0f *vP1[0] + 4.0f * vP2[0] - vP3[0]) * t2 +
		(-vP0[0] + 3.0f*vP1[0] - 3.0f *vP2[0] + vP3[0]) * t3);
	// Y
	vOut[1] = 0.5f * ((2.0f * vP1[1]) +
		(-vP0[1] + vP2[1]) * t +
		(2.0f * vP0[1] - 5.0f *vP1[1] + 4.0f * vP2[1] - vP3[1]) * t2 +
		(-vP0[1] + 3.0f*vP1[1] - 3.0f *vP2[1] + vP3[1]) * t3);

	// Z
	vOut[2] = 0.5f * ((2.0f * vP1[2]) +
		(-vP0[2] + vP2[2]) * t +
		(2.0f * vP0[2] - 5.0f *vP1[2] + 4.0f * vP2[2] - vP3[2]) * t2 +
		(-vP0[2] + 3.0f*vP1[2] - 3.0f *vP2[2] + vP3[2]) * t3);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// This function does a three dimensional Catmull-Rom curve interpolation. Pass four points, and a
// floating point number between 0.0 and 1.0. The curve is interpolated between the middle two points.
// Coded by RSW
// http://www.mvps.org/directx/articles/catmull/
void m3dCatmullRom3(M3DVector3d vOut, M3DVector3d vP0, M3DVector3d vP1, M3DVector3d vP2, M3DVector3d vP3, double t)
{
	// Unrolled loop to speed things up a little bit...
	double t2 = t * t;
	double t3 = t2 * t;

	// X    
	vOut[0] = 0.5 * ((2.0 * vP1[0]) +
		(-vP0[0] + vP2[0]) * t +
		(2.0 * vP0[0] - 5.0 *vP1[0] + 4.0 * vP2[0] - vP3[0]) * t2 +
		(-vP0[0] + 3.0*vP1[0] - 3.0 *vP2[0] + vP3[0]) * t3);
	// Y
	vOut[1] = 0.5 * ((2.0 * vP1[1]) +
		(-vP0[1] + vP2[1]) * t +
		(2.0 * vP0[1] - 5.0 *vP1[1] + 4.0 * vP2[1] - vP3[1]) * t2 +
		(-vP0[1] + 3 * vP1[1] - 3.0 *vP2[1] + vP3[1]) * t3);

	// Z
	vOut[2] = 0.5 * ((2.0 * vP1[2]) +
		(-vP0[2] + vP2[2]) * t +
		(2.0 * vP0[2] - 5.0 *vP1[2] + 4.0 * vP2[2] - vP3[2]) * t2 +
		(-vP0[2] + 3.0*vP1[2] - 3.0 *vP2[2] + vP3[2]) * t3);
}


///////////////////////////////////////////////////////////////////////////////
// Determine if the ray (starting at point) intersects the sphere centered at
// sphereCenter with radius sphereRadius
// Return value is < 0 if the ray does not intersect
// Return value is 0.0 if ray is tangent
// Positive value is distance to the intersection point
// Algorithm from "3D Math Primer for Graphics and Game Development"
double m3dRaySphereTest(const M3DVector3d point, const M3DVector3d ray, const M3DVector3d sphereCenter, double sphereRadius)
{
	//m3dNormalizeVector(ray);	// Make sure ray is unit length

	M3DVector3d rayToCenter;	// Ray to center of sphere
	rayToCenter[0] = sphereCenter[0] - point[0];
	rayToCenter[1] = sphereCenter[1] - point[1];
	rayToCenter[2] = sphereCenter[2] - point[2];

	// Project rayToCenter on ray to test
	double a = m3dDotProduct(rayToCenter, ray);

	// Distance to center of sphere
	double distance2 = m3dDotProduct(rayToCenter, rayToCenter);	// Or length


	double dRet = (sphereRadius * sphereRadius) - distance2 + (a*a);

	if (dRet > 0.0)			// Return distance to intersection
		dRet = a - sqrt(dRet);

	return dRet;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if the ray (starting at point) intersects the sphere centered at
// ditto above, but uses floating point math
float m3dRaySphereTest(const M3DVector3f point, const M3DVector3f ray, const M3DVector3f sphereCenter, float sphereRadius)
{
	//m3dNormalizeVectorf(ray);	// Make sure ray is unit length

	M3DVector3f rayToCenter;	// Ray to center of sphere
	rayToCenter[0] = sphereCenter[0] - point[0];
	rayToCenter[1] = sphereCenter[1] - point[1];
	rayToCenter[2] = sphereCenter[2] - point[2];

	// Project rayToCenter on ray to test
	float a = m3dDotProduct(rayToCenter, ray);

	// Distance to center of sphere
	float distance2 = m3dDotProduct(rayToCenter, rayToCenter);	// Or length

	float dRet = (sphereRadius * sphereRadius) - distance2 + (a*a);

	if (dRet > 0.0)			// Return distance to intersection
		dRet = a - sqrtf(dRet);

	return dRet;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Calculate the tangent basis for a triangle on the surface of a model
// This vector is needed for most normal mapping shaders 
void m3dCalculateTangentBasis(const M3DVector3f vTriangle[3], const M3DVector2f vTexCoords[3], const M3DVector3f N, M3DVector3f vTangent)
{
	M3DVector3f dv2v1, dv3v1;
	float dc2c1t, dc2c1b, dc3c1t, dc3c1b;
	float M;

	m3dSubtractVectors3(dv2v1, vTriangle[1], vTriangle[0]);
	m3dSubtractVectors3(dv3v1, vTriangle[2], vTriangle[0]);

	dc2c1t = vTexCoords[1][0] - vTexCoords[0][0];
	dc2c1b = vTexCoords[1][1] - vTexCoords[0][1];
	dc3c1t = vTexCoords[2][0] - vTexCoords[0][0];
	dc3c1b = vTexCoords[2][1] - vTexCoords[0][1];

	M = (dc2c1t * dc3c1b) - (dc3c1t * dc2c1b);
	M = 1.0f / M;

	m3dScaleVector3(dv2v1, dc3c1b);
	m3dScaleVector3(dv3v1, dc2c1b);

	m3dSubtractVectors3(vTangent, dv2v1, dv3v1);
	m3dScaleVector3(vTangent, M);  // This potentially changes the direction of the vector
	m3dNormalizeVector(vTangent);

	M3DVector3f B;
	m3dCrossProduct(B, N, vTangent);
	m3dCrossProduct(vTangent, B, N);
	m3dNormalizeVector(vTangent);
}


////////////////////////////////////////////////////////////////////////////
// Smoothly step between 0 and 1 between edge1 and edge 2
double m3dSmoothStep(double edge1, double edge2, double x)
{
	double t;
	t = (x - edge1) / (edge2 - edge1);
	if (t > 1.0)
		t = 1.0;

	if (t < 0.0)
		t = 0.0f;

	return t * t * (3.0 - 2.0 * t);
}

////////////////////////////////////////////////////////////////////////////
// Smoothly step between 0 and 1 between edge1 and edge 2
float m3dSmoothStep(float edge1, float edge2, float x)
{
	float t;
	t = (x - edge1) / (edge2 - edge1);
	if (t > 1.0f)
		t = 1.0f;

	if (t < 0.0)
		t = 0.0f;

	return t * t * (3.0f - 2.0f * t);
}



///////////////////////////////////////////////////////////////////////////
// Creae a projection to "squish" an object into the plane.
// Use m3dGetPlaneEquationf(planeEq, point1, point2, point3);
// to get a plane equation.
void m3dMakePlanarShadowMatrix(M3DMatrix44f proj, const M3DVector4f planeEq, const M3DVector3f vLightPos)
{
	// These just make the code below easier to read. They will be 
	// removed by the optimizer.	
	float a = planeEq[0];
	float b = planeEq[1];
	float c = planeEq[2];
	float d = planeEq[3];

	float dx = -vLightPos[0];
	float dy = -vLightPos[1];
	float dz = -vLightPos[2];

	// Now build the projection matrix
	proj[0] = b * dy + c * dz;
	proj[1] = -a * dy;
	proj[2] = -a * dz;
	proj[3] = 0.0;

	proj[4] = -b * dx;
	proj[5] = a * dx + c * dz;
	proj[6] = -b * dz;
	proj[7] = 0.0;

	proj[8] = -c * dx;
	proj[9] = -c * dy;
	proj[10] = a * dx + b * dy;
	proj[11] = 0.0;

	proj[12] = -d * dx;
	proj[13] = -d * dy;
	proj[14] = -d * dz;
	proj[15] = a * dx + b * dy + c * dz;
	// Shadow matrix ready
}


///////////////////////////////////////////////////////////////////////////
// Creae a projection to "squish" an object into the plane.
// Use m3dGetPlaneEquationd(planeEq, point1, point2, point3);
// to get a plane equation.
void m3dMakePlanarShadowMatrix(M3DMatrix44d proj, const M3DVector4d planeEq, const M3DVector3f vLightPos)
{
	// These just make the code below easier to read. They will be 
	// removed by the optimizer.	
	double a = planeEq[0];
	double b = planeEq[1];
	double c = planeEq[2];
	double d = planeEq[3];

	double dx = -vLightPos[0];
	double dy = -vLightPos[1];
	double dz = -vLightPos[2];

	// Now build the projection matrix
	proj[0] = b * dy + c * dz;
	proj[1] = -a * dy;
	proj[2] = -a * dz;
	proj[3] = 0.0;

	proj[4] = -b * dx;
	proj[5] = a * dx + c * dz;
	proj[6] = -b * dz;
	proj[7] = 0.0;

	proj[8] = -c * dx;
	proj[9] = -c * dy;
	proj[10] = a * dx + b * dy;
	proj[11] = 0.0;

	proj[12] = -d * dx;
	proj[13] = -d * dy;
	proj[14] = -d * dz;
	proj[15] = a * dx + b * dy + c * dz;
	// Shadow matrix ready
}


/////////////////////////////////////////////////////////////////////////////
// I want to know the point on a ray, closest to another given point in space.
// As a bonus, return the distance squared of the two points.
// In: vRayOrigin is the origin of the ray.
// In: vUnitRayDir is the unit vector of the ray
// In: vPointInSpace is the point in space
// Out: vPointOnRay is the poing on the ray closest to vPointInSpace
// Return: The square of the distance to the ray
double m3dClosestPointOnRay(M3DVector3d vPointOnRay, const M3DVector3d vRayOrigin, const M3DVector3d vUnitRayDir,
	const M3DVector3d vPointInSpace)
{
	M3DVector3d v;
	m3dSubtractVectors3(v, vPointInSpace, vRayOrigin);

	double t = m3dDotProduct(vUnitRayDir, v);

	// This is the point on the ray
	vPointOnRay[0] = vRayOrigin[0] + (t * vUnitRayDir[0]);
	vPointOnRay[1] = vRayOrigin[1] + (t * vUnitRayDir[1]);
	vPointOnRay[2] = vRayOrigin[2] + (t * vUnitRayDir[2]);

	return m3dGetDistanceSquared(vPointOnRay, vPointInSpace);
}

// ditto above... but with floats
float m3dClosestPointOnRay(M3DVector3f vPointOnRay, const M3DVector3f vRayOrigin, const M3DVector3f vUnitRayDir,
	const M3DVector3f vPointInSpace)
{
	M3DVector3f v;
	m3dSubtractVectors3(v, vPointInSpace, vRayOrigin);

	float t = m3dDotProduct(vUnitRayDir, v);

	// This is the point on the ray
	vPointOnRay[0] = vRayOrigin[0] + (t * vUnitRayDir[0]);
	vPointOnRay[1] = vRayOrigin[1] + (t * vUnitRayDir[1]);
	vPointOnRay[2] = vRayOrigin[2] + (t * vUnitRayDir[2]);

	return m3dGetDistanceSquared(vPointOnRay, vPointInSpace);
}
