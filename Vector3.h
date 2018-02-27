#pragma once
class Vector3
{
public:
	float x, y, z;

	Vector3(float fx, float fy, float fz);

	Vector3 operator + (const Vector3& right) const;
	Vector3 operator - (const Vector3& right) const;
	Vector3 operator * (float value) const;

	float static Dot(const Vector3& left, const Vector3& right);
	Vector3 static Cross(const Vector3& left, const Vector3& right);

};
