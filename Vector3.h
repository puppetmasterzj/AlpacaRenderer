#pragma once
class Vector3
{
public:
	float x, y, z;

	Vector3(float fx, float fy, float fz);

	inline Vector3 operator + (const Vector3& right) const;
	inline Vector3 operator - (const Vector3& right) const;
	inline Vector3 operator * (float value) const;
	inline Vector3 operator / (float value) const;
	inline float SquareMagnitude();
	inline float Magnitude();
	inline void Normalize();

	inline float static Dot(const Vector3& left, const Vector3& right);
	inline Vector3 static Cross(const Vector3& left, const Vector3& right);
	inline Vector3 static Lerp(const Vector3& left, const Vector3& right, float t);
};
