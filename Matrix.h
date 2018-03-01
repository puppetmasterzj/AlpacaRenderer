#pragma once
#include"Vector3.h"

class Matrix
{
public:

	float value[4][4];

	Matrix();
	~Matrix();

	Matrix operator + (const Matrix& right) const;
	Matrix operator - (const Matrix& right) const;
	Matrix operator * (const Matrix& right) const;
	Matrix operator * (float k) const;

	Vector3 MultiplyVector3(const Vector3& v) const;
	void Identity();
	void Transpose();

	static Matrix GenTranslateMatrix(const Vector3& v);
	static Matrix GenRotationMatrix(const Vector3& anxi, float angle);
	static Matrix GenScaleMatrix(const Vector3& v);

	void Print();

};

