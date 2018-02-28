#include "Vector3.h"
#include "ApcMath.h"

Vector3::Vector3(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

Vector3 Vector3::operator+(const Vector3& right)const
{
	Vector3 returnValue(x + right.x, y + right.y, z + right.z);
	return returnValue;
}

Vector3 Vector3::operator-(const Vector3& right)const
{
	Vector3 returnValue(x - right.x, y - right.y, z - right.z);
	return returnValue;
}

Vector3 Vector3::operator*(float value)const
{
	Vector3 returnValue(x * value, y * value, z * value);
	return returnValue;
}

Vector3 Vector3::operator/(float value)const
{
	Vector3 returnValue(x / value, y / value, z / value);
	return returnValue;
}

float Vector3::SquareMagnitude()
{
	return Dot(*this, *this);
}

float Vector3::Magnitude()
{
	return sqrt(SquareMagnitude());
}

void Vector3::Normalize()
{
	*this / Magnitude();
}

float Vector3::Dot(const Vector3& left, const Vector3& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector3 Vector3::Cross(const Vector3& left, const Vector3& right)
{
	float valueX = left.y * right.z - left.z * right.y;
	float valueY = left.z * right.x - left.x * right.z;
	float valueZ = left.x * right.y - left.y * right.x;
	Vector3 returnValue(valueX, valueY, valueZ);
	return returnValue;
}

Vector3 Vector3::Lerp(const Vector3& left, const Vector3& right, float t)
{
	return left * t + right * (1.0f - t);
}


