#include "Stdfx.h"
#pragma once
class Vector3
{
public:
	float x, y, z;

	Vector3(float fx, float fy, float fz);

	 Vector3 operator + (const Vector3& right) const;
	 Vector3 operator - (const Vector3& right) const;
	 Vector3 operator * (float value) const;
	 Vector3 operator / (float value) const;
	 float SquareMagnitude();
	 float Magnitude();
	 void Normalize();

	float static Dot(const Vector3& left, const Vector3& right);
	Vector3 static Cross(const Vector3& left, const Vector3& right);
	inline Vector3 static Lerp(const Vector3& left, const Vector3& right, float t);

	void Print();
};
