#pragma once


#ifdef USE_ROW_MAJOR
#define ROW_MAJOR_ORDER	1
#endif

#define NOMINMAX
# define M_PI			3.14159265358979323846f
# define RADIANS		(M_PI / 180.f)
# define DEGREES		(180.f / M_PI)

#include <algorithm>
#include <iostream>


#undef min
#undef max

#include <assert.h>
#include <ostream>
#include <iomanip>
#include <algorithm>

struct vec2f
{
	vec2f() : x(0.0f), y(0.0f) {}
	vec2f(float x) : x(x), y(x) {}
	vec2f(float x, float y) : x(x), y(y) {}

	vec2f& operator+=(const vec2f& v);
	vec2f& operator-=(const vec2f& v);
	vec2f& operator*=(const vec2f& v);
	vec2f& operator/=(const vec2f& v);
	bool operator==(const vec2f& v);
	bool operator!=(const vec2f& v);



	float lenght2() const;
	float lenght() const;
	float dot(const vec2f& v);
	float x, y;

	static float dot(const vec2f& v1, const vec2f& v2);

	friend std::ostream& operator<< (std::ostream& o, const vec2f& v);

};

inline std::ostream& operator<< (std::ostream& o, const vec2f& v) {
	return o << "vec2( " << v.x << ", " << v.y << ")";
}

inline vec2f& vec2f::operator+=(const vec2f& v)
{
	x += v.x;
	y += v.y;

	return *this;
}

inline vec2f& vec2f::operator-=(const vec2f& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

inline vec2f& vec2f::operator*=(const vec2f& v)
{
	x *= v.x;
	y *= v.y;

	return *this;
}

inline vec2f& vec2f::operator/=(const vec2f& v)
{
	x /= v.x;
	y /= v.y;

	return *this;
}

inline float vec2f::lenght2() const
{
	return (x * x) + (y * y);
}

inline float vec2f::lenght() const
{
	return sqrtf(lenght2()); // == |A|
}

inline float vec2f::dot(const vec2f& v)
{
	return x * v.x + y * v.y;
}

inline float vec2f::dot(const vec2f& v1, const vec2f& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}
inline vec2f operator-(const vec2f& v1, const vec2f& v2) {
	return vec2f(v1.x - v2.x, v1.y - v2.y);
}

inline bool vec2f::operator==(const vec2f& v) {
	return (x == v.x && y == v.y);
}

inline bool vec2f::operator!=(const vec2f& v) {
	return !(*this == v);
}


class vec3f
{
public:
	float x, y, z;
	vec3f() : x(0.0), y(0.0), z(0.0) {}
	vec3f(const vec3f& v) : x(v.x), y(v.y), z(v.z) {}
	vec3f(float x, float y, float z) : x(x), y(y), z(z) {}
	//explicit vec3f(int x, int y, int z) : x((float)x), y((float)y), z((float)z) {}
	explicit vec3f(float f) : x(f), y(f), z(f) {}

	float& operator[](unsigned int i);
	float operator[](unsigned int i) const;

	vec3f& operator = (const vec3f& v);
	vec3f operator-() const;
	vec3f& operator+=(const vec3f& v);
	vec3f& operator-=(const vec3f& v);
	vec3f& operator*=(const vec3f& v);
	vec3f& operator/=(const vec3f& v);
	vec3f& operator*=(const float& f);
	vec3f& operator/= (const float& f);

	/*----------------- LOCAL -------------------------*/
	float length2() const;
	float length() const;
	float normalize();
	vec3f normalized() const;
	vec3f negative() const;
	inline float dot(const vec3f& v);
	inline vec3f cross(const vec3f& v);

	/*----------------- STATICS -----------------------*/
	static float dot(const vec3f& v1, const vec3f& v2);
	static float fabsdot(const vec3f& v1, const vec3f& v2);
	static vec3f cross(const vec3f& v1, const vec3f& v2);
	static vec3f reflect(const vec3f& dir, const vec3f& n);
	static vec3f min(const vec3f& v1, const vec3f& v2);
	static vec3f max(const vec3f& v1, const vec3f& v2);
	static vec3f lerp(const vec3f& start, const vec3f& end, float factor);

	/*-------------------------------------------------*/
	float maxComponent() const { return std::max(std::max(x, y), z); }
	float minComponent() const { return std::min(std::min(x, y), z); }

	friend std::ostream& operator<<(std::ostream& o, const vec3f& v);
};

inline float& vec3f::operator[](unsigned int i)
{
	assert(i >= 0 && i <= 2);
	return (&x)[i];
}
inline float vec3f::operator[](unsigned int i) const
{
	assert(i >= 0 && i <= 2);
	return (&x)[i];
}

inline vec3f& vec3f::operator=(const vec3f& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
inline vec3f vec3f::operator-() const
{
	return vec3f(-x, -y, -z);
}

inline vec3f& vec3f::operator+=(const vec3f& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline vec3f& vec3f::operator-=(const vec3f& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline vec3f& vec3f::operator*=(const vec3f& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

inline vec3f& vec3f::operator/=(const vec3f& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

inline vec3f& vec3f::operator*=(const float& f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

inline vec3f& vec3f::operator/=(const float& f)
{
	float inv = 1.f / f;
	x *= inv;
	y *= inv;
	z *= inv;
	return *this;
}

//EXTERNAL OPERATOR

inline vec3f operator+(const vec3f& v1, const vec3f& v2)
{
	return vec3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline vec3f operator-(const vec3f& v1, const vec3f& v2)
{
	return vec3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline vec3f operator*(const vec3f& v1, const vec3f& v2)
{
	return vec3f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline vec3f operator*(const vec3f& v, float f)
{
	return vec3f(f * v.x, f * v.y, f * v.z);
}

inline vec3f operator*(float f, const vec3f& v)
{
	return vec3f(f * v.x, f * v.y, f * v.z);
}

inline vec3f operator/(const vec3f& v, float f)
{
	float inv = 1.f / f;
	return vec3f(v.x * inv, v.y * inv, v.z * inv);
}

inline vec3f operator/(float f, const vec3f& v)
{
	return vec3f(f / v.x, f / v.y, f / v.z);
}

inline vec3f operator/(const vec3f& v1, const vec3f& v2)
{
	return vec3f(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline bool operator==(const vec3f& r, const vec3f& l)
{
	return (r.x == l.x && r.y == l.y && r.z == l.z);
}

inline bool operator!=(const vec3f& r, const vec3f& l)
{
	return (r.x != l.x && r.y != l.y && r.z != l.z);
}

inline bool operator>(const vec3f& r, const vec3f& l)
{
	return (r.length2() > l.length2());
}

inline bool operator<(const vec3f& r, const vec3f& l)
{
	return (r.length2() < l.length2());
}

//FUNC

inline float vec3f::length2() const
{
	return x * x + y * y + z * z;
}

inline float vec3f::length() const
{
	return std::sqrt(length2());
}

inline float vec3f::normalize()
{
	float len = length(); *this /= len; return len;
}

inline vec3f vec3f::normalized() const
{
	vec3f nor(*this);
	nor.normalize();
	return nor;
}

inline vec3f vec3f::negative() const
{
	return vec3f(-x, -y, -z);
}

inline float vec3f::dot(const vec3f& v)
{
	return x * v.x + y * v.y + z * v.z;
}
inline vec3f vec3f::cross(const vec3f& v)
{
	return vec3f(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}

//STATICS

inline float vec3f::dot(const vec3f& v1, const vec3f& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float vec3f::fabsdot(const vec3f& v1, const vec3f& v2)
{
	return fabs(vec3f::dot(v1, v2));
}

inline vec3f vec3f::cross(const vec3f& v1, const vec3f& v2)
{
	return vec3f(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

inline vec3f vec3f::reflect(const vec3f& dir, const vec3f& n)
{
	return dir - n * 2 * vec3f::dot(n, dir);
}

inline vec3f vec3f::min(const vec3f& v1, const vec3f& v2)
{
	return vec3f(
		std::min(v1.x, v2.x),
		std::min(v1.y, v2.y),
		std::min(v1.z, v2.z));
}

inline vec3f vec3f::max(const vec3f& v1, const vec3f& v2)
{
	return vec3f(
		std::max(v1.x, v2.x),
		std::max(v1.y, v2.y),
		std::max(v1.z, v2.z));
}

inline vec3f vec3f::lerp(const vec3f& start, const vec3f& end, float factor)
{
	return start + (end - start) * factor;
	//return (start + vec3f(factor) * (end - start));
}

inline std::ostream& operator<<(std::ostream& o, const vec3f& v)
{
	o << "vec3( " << v.x << ", " << v.y << " ," << v.z << ')';
	return o;
}

struct vec4f {
	vec4f() : x(0.f), y(0.f), z(0.f), w(0.f) {};
	vec4f(float x) : x(x), y(x), z(x), w(x) {};
	vec4f(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}
	vec4f(const vec3f& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(1.f){}

	float x, y, z, w;

	bool operator==(const vec4f& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
};

__declspec(align(16))
struct mat4x4 {
	//static float radians = 3.14159265358979323846f / 180.f;
	mat4x4();
	mat4x4(float* rhs);

	mat4x4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);

	mat4x4 operator*(const mat4x4& rhs);
	vec3f operator*(const vec3f& v);

	void SetIdentity();

	float* data();
	float* operator[](unsigned int i);
	const float* operator[](unsigned int i) const;

	mat4x4 inverted();

	static mat4x4 transposed(const mat4x4& m);
	static mat4x4 transposedTranslation(const mat4x4& rhs);
	//Static
	static mat4x4 scaled(const vec3f& v);

	static mat4x4 translated(const vec3f& t);

	//ROTATE Functions;
	static mat4x4 rotateX(float angle);
	static mat4x4 rotateY(float angle);
	static mat4x4 rotateZ(float angle);
	//----------------------------------

	static mat4x4 perspective_lh(float fovY, float ratioX, float znear, float zfar);
	static mat4x4 orthographic_lh(float width, float height, float znear, float zfar);
	static mat4x4 look_at(const vec3f& pos, const vec3f& center, const vec3f& worldUp);
	static mat4x4 yaw_pitch_roll(float yaw, float pitch, float roll);
	static mat4x4 rotation_axis(const vec3f& v, float angle);

	//method

	static mat4x4 ndc_to_screen(int width, int height);

	union {
		float f[16];
		float m[4][4];
	};

};

inline mat4x4::mat4x4() {
	SetIdentity();
};
inline mat4x4::mat4x4(float* rhs) {
	memcpy_s(f, sizeof(f), rhs, sizeof(f));
};

inline mat4x4::mat4x4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33
) {
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

inline mat4x4 mat4x4::operator*(const mat4x4& rhs) {
	mat4x4 mat;
	//00 01 02 03          //00 01 02 03
	//10 11 12 13		   //10 11 12 13
	//20 21 22 23		   //20 21 22 23
	//30 31 32 33		   //30 31 32 33

	//column
	//mat[0][0] = mat[0][0] * rhs[0][0] +
	//			  mat[0][1] * rhs[1][0] +
	//			  mat[0][2] * rhs[2][0] +
	//			  mat[0][3] * rhs[3][0];

	//mat[1][0] = mat[1][0] * rhs[0][1] +
	//			  mat[1][1] * rhs[1][1] +
	//			  mat[1][2] * rhs[2][1] +
	//			  mat[1][3] * rhs[3][1];
	//row
	//mat[0][0] = mat[0][0] * rhs[0][0] +
	//			  mat[1][0] * rhs[0][1] +
	//			  mat[2][0] * rhs[0][2] +
	//			  mat[3][0] * rhs[0][3];

#ifdef ROW_MAJOR_ORDER
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
	/*		mat[col][row] =
				m[row][0] * rhs[0][col] +
				m[row][1] * rhs[1][col] +
				m[row][2] * rhs[2][col] +
				m[row][3] * rhs[3][col];*/
			for (int i = 0; i < 4; ++i) {
				//mat[row][col] += m[row][i] * rhs[i][col];
				mat[row][col] =
					m[row][0] * rhs[0][col] +
					m[row][1] * rhs[1][col] +
					m[row][2] * rhs[2][col] +
					m[row][3] * rhs[3][col];
			}
		}
	}
#else
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			mat[col][row] = 
				m[row][0] * rhs[0][col] +
				m[row][1] * rhs[1][col] +
				m[row][2] * rhs[2][col] +
				m[row][3] * rhs[3][col];
		}
	}
#endif
	return mat;
}

inline mat4x4 mat4x4::inverted()
{
	float inv[16] = {};
	float det = 0.0f;
	int i;

	inv[0] = f[5] * f[10] * f[15] -
		f[5] * f[11] * f[14] -
		f[9] * f[6] * f[15] +
		f[9] * f[7] * f[14] +
		f[13] * f[6] * f[11] -
		f[13] * f[7] * f[10];

	inv[4] = -f[4] * f[10] * f[15] +
		f[4] * f[11] * f[14] +
		f[8] * f[6] * f[15] -
		f[8] * f[7] * f[14] -
		f[12] * f[6] * f[11] +
		f[12] * f[7] * f[10];

	inv[8] = f[4] * f[9] * f[15] -
		f[4] * f[11] * f[13] -
		f[8] * f[5] * f[15] +
		f[8] * f[7] * f[13] +
		f[12] * f[5] * f[11] -
		f[12] * f[7] * f[9];

	inv[12] = -f[4] * f[9] * f[14] +
		f[4] * f[10] * f[13] +
		f[8] * f[5] * f[14] -
		f[8] * f[6] * f[13] -
		f[12] * f[5] * f[10] +
		f[12] * f[6] * f[9];

	inv[1] = -f[1] * f[10] * f[15] +
		f[1] * f[11] * f[14] +
		f[9] * f[2] * f[15] -
		f[9] * f[3] * f[14] -
		f[13] * f[2] * f[11] +
		f[13] * f[3] * f[10];

	inv[5] = f[0] * f[10] * f[15] -
		f[0] * f[11] * f[14] -
		f[8] * f[2] * f[15] +
		f[8] * f[3] * f[14] +
		f[12] * f[2] * f[11] -
		f[12] * f[3] * f[10];

	inv[9] = -f[0] * f[9] * f[15] +
		f[0] * f[11] * f[13] +
		f[8] * f[1] * f[15] -
		f[8] * f[3] * f[13] -
		f[12] * f[1] * f[11] +
		f[12] * f[3] * f[9];

	inv[13] = f[0] * f[9] * f[14] -
		f[0] * f[10] * f[13] -
		f[8] * f[1] * f[14] +
		f[8] * f[2] * f[13] +
		f[12] * f[1] * f[10] -
		f[12] * f[2] * f[9];

	inv[2] = f[1] * f[6] * f[15] -
		f[1] * f[7] * f[14] -
		f[5] * f[2] * f[15] +
		f[5] * f[3] * f[14] +
		f[13] * f[2] * f[7] -
		f[13] * f[3] * f[6];

	inv[6] = -f[0] * f[6] * f[15] +
		f[0] * f[7] * f[14] +
		f[4] * f[2] * f[15] -
		f[4] * f[3] * f[14] -
		f[12] * f[2] * f[7] +
		f[12] * f[3] * f[6];

	inv[10] = f[0] * f[5] * f[15] -
		f[0] * f[7] * f[13] -
		f[4] * f[1] * f[15] +
		f[4] * f[3] * f[13] +
		f[12] * f[1] * f[7] -
		f[12] * f[3] * f[5];

	inv[14] = -f[0] * f[5] * f[14] +
		f[0] * f[6] * f[13] +
		f[4] * f[1] * f[14] -
		f[4] * f[2] * f[13] -
		f[12] * f[1] * f[6] +
		f[12] * f[2] * f[5];

	inv[3] = -f[1] * f[6] * f[11] +
		f[1] * f[7] * f[10] +
		f[5] * f[2] * f[11] -
		f[5] * f[3] * f[10] -
		f[9] * f[2] * f[7] +
		f[9] * f[3] * f[6];

	inv[7] = f[0] * f[6] * f[11] -
		f[0] * f[7] * f[10] -
		f[4] * f[2] * f[11] +
		f[4] * f[3] * f[10] +
		f[8] * f[2] * f[7] -
		f[8] * f[3] * f[6];

	inv[11] = -f[0] * f[5] * f[11] +
		f[0] * f[7] * f[9] +
		f[4] * f[1] * f[11] -
		f[4] * f[3] * f[9] -
		f[8] * f[1] * f[7] +
		f[8] * f[3] * f[5];

	inv[15] = f[0] * f[5] * f[10] -
		f[0] * f[6] * f[9] -
		f[4] * f[1] * f[10] +
		f[4] * f[2] * f[9] +
		f[8] * f[1] * f[6] -
		f[8] * f[2] * f[5];

	det = f[0] * inv[0] + f[1] * inv[4] + f[2] * inv[8] + f[3] * inv[12];

	if (det == 0)
		return mat4x4();

	det = 1.0f / det;

	mat4x4 mat{};
	for (i = 0; i < 16; i++)
		mat.f[i] = inv[i] * det;

	return mat;
}

inline vec3f mat4x4::operator*(const vec3f& v)
{
	float x, y, z;

#ifdef ROW_MAJOR_ORDER
	x = (v.x * m[0][0]) + (v.y * m[1][0]) + (v.z * m[2][0]) + m[3][0];
	y = (v.x * m[0][1]) + (v.y * m[1][1]) + (v.z * m[2][1]) + m[3][1];
	z = (v.x * m[0][2]) + (v.y * m[1][2]) + (v.z * m[2][2]) + m[3][2];
	float w = (v.x * m[3][0]) + (v.y * m[3][1]) + (v.z * m[3][2]) + m[3][3];
#else
	//column major
	x = (v.x * m[0][0]) + (v.y * m[0][1]) + (v.z * m[0][2]) + m[0][3];
	y = (v.x * m[1][0]) + (v.y * m[1][1]) + (v.z * m[1][2]) + m[1][3];
	z = (v.x * m[2][0]) + (v.y * m[2][1]) + (v.z * m[2][2]) + m[2][3];
#endif
	//x /= w;
	//y /= w;
	//z /= w;
	return vec3f(x, y, z);
}

inline void mat4x4::SetIdentity() {
	memset(f, 0, sizeof(f));
	m[0][0] = 1.f;
	m[1][1] = 1.f;
	m[2][2] = 1.f;
	m[3][3] = 1.f;
};

inline float* mat4x4::data() {
	return f;
};
inline float* mat4x4::operator[](unsigned int i) {
	return m[i];
}
inline const float* mat4x4::operator[](unsigned int i) const {
	return m[i];
}

inline mat4x4 mat4x4::transposed(const mat4x4& m) {
	mat4x4 mat = {
		m[0][0],m[1][0],m[2][0],m[3][0],
		m[0][1],m[1][1],m[2][1],m[3][1],
		m[0][2],m[1][2],m[2][2],m[3][2],
		m[0][3],m[1][3],m[2][3],m[3][3]
	};

	return mat;
}

inline mat4x4 mat4x4::transposedTranslation(const mat4x4& rhs)
{
	mat4x4 mat;
	mat[0][3] = rhs[0][3] * -1.f;
	mat[1][3] = rhs[1][3] * -1.f;
	mat[2][3] = rhs[2][3] * -1.f;

	return mat;
}

//Static
inline mat4x4 mat4x4::scaled(const vec3f& v) {
	mat4x4 mat = {
	v.x,0.f,0.f,0.f,
	0.f,v.y,0.f,0.f,
	0.f,0.f,v.z,0.f,
	0.f,0.f,0.f,1.f
	};

	return mat;
};

inline mat4x4 mat4x4::translated(const vec3f& t) {

#ifdef ROW_MAJOR_ORDER
	mat4x4 mat = {
	1.f,0.f,0.f,0.f,
	0.f,1.f,0.f,0.f,
	0.f,0.f,1.f,0.f,
	t.x,t.y,t.z,1.f
	};

	return mat;
#else
	mat4x4 mat = {
	1.f,0.f,0.f,t.x,
	0.f,1.f,0.f,t.y,
	0.f,0.f,1.f,t.z,
	0.f,0.f,0.f,1.f
	};

	return mat;
#endif
}

//ROTATE Functions;
inline mat4x4 mat4x4::rotateX(float angle) {
	float theta = angle * RADIANS;
	mat4x4 mat = {
	1.f,0.f,0.f,0.f,
	0.f,cos(theta),-sin(theta),0.f,
	0.f,sin(theta),cos(theta),0.f,
	0.f,0.f,0.f,1.f
	};

	return mat;
}
inline mat4x4 mat4x4::rotateY(float angle) {
	float theta = angle * RADIANS;
	mat4x4 mat = {
	cos(theta),0.f,sin(theta),0.f,
	0.f,1.f,0.f,0.f,
	-sin(theta),0.f,cos(theta),0.f,
	0.f,0.f,0.f,1.f
	};

	return mat;
}
inline mat4x4 mat4x4::rotateZ(float angle) {
	float theta = angle * RADIANS;
	float sinx = sin(theta);
	float cosx = cos(theta);
	mat4x4 mat = {
	cosx,-sinx,0.f,0.f,
	sinx,cosx,0.f,0.f,
	0.f,0.f,1.f,0.f,
	0.f,0.f,0.f,1.f
	};

	return mat;
}
//----------------------------------

inline mat4x4 mat4x4::perspective_lh(float fovY, float ratioX, float znear, float zfar)
{
	float halfFov = fovY * 0.5f;
	const float tanFov = std::tan(RADIANS * halfFov);

	float A = 1.f / (ratioX * tanFov);
	float B = 1.f / tanFov;
	float C = zfar / (zfar - znear);
	float D = (-znear * zfar) / (zfar - znear);
	float E = 1.f;

	mat4x4 mat = {
		  A,0.f,0.f,0.f,
		0.f,  B,0.f,0.f,
		0.f,0.f,  C,  D,
		0.f,0.f,  E,0.f
	};

	return mat;
}

inline mat4x4 mat4x4::orthographic_lh(float width, float height, float znear, float zfar)
{
	float range = 1.f / (zfar - znear);
	mat4x4 mat = {
		2.f / width, 0.f         , 0.f  ,            0.f,
		0.f        , 2.f / height, 0.f  ,            0.f,
		0.f        , 0.f         , range, -range * znear,
		0.f        , 0.f         , 0.f  ,            1.f     
	};
	return mat;
}

inline mat4x4 mat4x4::look_at(const vec3f& pos, const vec3f& center, const vec3f& worldUp)
{
	vec3f f = (center - pos).normalized();
	vec3f r = vec3f::cross(worldUp, f).normalized();
	vec3f u = vec3f::cross(f, r).normalized();

	float x = -vec3f::dot(r, pos);
	float y = -vec3f::dot(u, pos);
	float z = -vec3f::dot(f, pos);

	mat4x4 m = {
		r.x,r.y,r.z,x,
		u.x,u.y,u.z,y,
		f.x,f.y,f.z,z,
		0,0,0,1
	};

	return m;
}

inline mat4x4 mat4x4::yaw_pitch_roll(float yaw, float pitch, float roll)
{
	//https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

	//          yaw               pitch                roll
	// |  cosy   0  siny     1      0      0  |     | cosz  -sinz    0 |
	// |     0   1     0  *  0   cosx  -sinx  |  *  | sinz   cosz    0 |
	// | -siny   0  cosy     0   sinx   cosx  |     |    0      0    1 |
	//
	//            (yaw * pitch)                       roll
	// |  cosy   siny*sinx   siny*cosx  |     | cosz  -sinz    0 |
	// |   0     cosx       -sinx	    |  *  | sinz   cosz    0 |
	// | -siny   cosy*sinx   cosy*cosx  |     |    0      0    1 |
	//
	//							Yaw * Pitch * Roll
	// | cosy*cosz + siny*sinx *sinz   cosy*-sinz+ siny*sinx*cosz   siny*cosx |
	// | cosx*sinz                     cosx*cosz                    -sinx	  |
	// | -siny*cosz+cosy*sinx*sinz     -siny*-sinz+cosy*sinx*cosz   cosy*cosx |

	yaw *= RADIANS;
	pitch *= RADIANS;
	roll *= RADIANS;

	float cosx = cos(pitch);
	float cosy = cos(yaw);
	float cosz = cos(roll);
	float sinx = sin(pitch);
	float siny = sin(yaw);
	float sinz = sin(roll);

	mat4x4 mat = {
			cosy * cosz + siny * sinx * sinz,  cosy * -sinz + siny * sinx * cosz,  siny * cosx,  0.0f,
			cosx * sinz,                    cosx * cosz,                    -sinx,      0.0f,
			-siny * cosz + cosy * sinx * sinz,  -siny * -sinz + cosy * sinx * cosz, cosy * cosx,  0.0f,
			0.0f,                         0.0f,                         0.0f,       1.0f
	};

	return mat;
}

inline mat4x4 mat4x4::rotation_axis(const vec3f& v, float angle)
{
	float theta = angle * RADIANS;
	float cosx = cos(v.x * theta);
	float cosy = cos(v.y * theta);
	float cosz = cos(v.z * theta);
	float sinx = sin(v.x * theta);
	float siny = sin(v.y * theta);
	float sinz = sin(v.z * theta);

	mat4x4 mat = {
		cosy * cosz + siny * sinx * sinz,  cosy * -sinz + siny * sinx * cosz,  siny * cosx,  0.0f,
		cosx * sinz,                    cosx * cosz,                    -sinx,      0.0f,
		-siny * cosz + cosy * sinx * sinz,  -siny * -sinz + cosy * sinx * cosz, cosy * cosx,  0.0f,
		0.0f,                         0.0f,                         0.0f,       1.0f
	};
	return mat;
}

inline mat4x4 mat4x4::ndc_to_screen(int width, int height)
{
	float sx = 2.f / (float)width;
	float sy = 2.f / (float)height;

#ifdef ROW_MAJOR_ORDER
	mat4x4 screen = {
		  sx,   0.0f,   0.0f,  0.f,
		0.0f,    -sy,   0.0f,  0.f,
		0.0f,   0.0f,   1.0f,  0.f,
	   -1.0f,   1.0f,   0.0f,  1.f
	};
	return screen;
#else
	mat4x4 screen = {
		sx,   0.0f, 0.0f, -1.f,
		0.0f,  -sy, 0.0f,  1.f,
		0.0f, 0.0f, 1.0f,  0.f,
		0.0f, 0.0f, 0.0f,  1.f
	};
	return screen;
#endif // ROW_MAJOR_ORDER

}

inline std::ostream& operator<<(std::ostream& o, const mat4x4& mat) {
#define FM std::setw(12)
	//row major order
	o << "mat4x4[" << "\n" <<
		FM << mat[0][0] << FM << mat[0][1] << FM << mat[0][2] << FM << mat[0][3] << "\n" <<
		FM << mat[1][0] << FM << mat[1][1] << FM << mat[1][2] << FM << mat[1][3] << "\n" <<
		FM << mat[2][0] << FM << mat[2][1] << FM << mat[2][2] << FM << mat[2][3] << "\n" <<
		FM << mat[3][0] << FM << mat[3][1] << FM << mat[3][2] << FM << mat[3][3] << " ]" << "\n";
#undef FM
	return o;
}

struct Rect
{
	int x, y, w, h;

	Rect() : x(0), y(0), w(0), h(0) {};
	Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {};	
	static bool IsPtInRect(const Rect& rc, int x, int y);
	static void LocalCoord(_In_ const Rect* parent, _Out_ Rect* src);
	static void OffsetRect(int x, int y, _Out_ Rect* src);
};

inline bool Rect::IsPtInRect(const Rect& rc, int x, int y) {
	if (rc.x <= x && (rc.x + rc.w) >= x &&
		rc.y < y && (rc.y + rc.h) > y)
		return true;
	return false;
}

inline void Rect::LocalCoord(const Rect* parent, Rect* src)
{
	src->x = parent->x + src->x;
	src->y = parent->y + src->y;
}

inline void Rect::OffsetRect(int x, int y, Rect* src)
{
	src->x -= x;
	src->y -= y;
	src->w += x * 2;
	src->h += y * 2;
}
