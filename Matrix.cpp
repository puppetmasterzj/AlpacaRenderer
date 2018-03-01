#include "Matrix.h"
#include "Stdfx.h"

Matrix::Matrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			value[i][j] = 0;
		}
	}
}

Matrix::~Matrix()
{
}

Matrix Matrix::operator + (const Matrix& right) const
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.value[i][j] = this->value[i][j] + right.value[i][j];
		}
	}
	return m;
}

Matrix Matrix::operator - (const Matrix& right) const
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.value[i][j] = this->value[i][j] - right.value[i][j];
		}
	}
	return m;
}

Matrix Matrix::operator * (const Matrix& right) const
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.value[i][j] = 0;//temp
			for (int k = 0; k < 4; k++)
			{
				m.value[i][j] += this->value[i][k] * right.value[k][j];
			}
		}
	}
	return m;
}

Matrix Matrix::operator * (float k) const
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.value[i][j] = this->value[i][j] * k;
		}
	}
	return m;
}

Vector3 Matrix::MultiplyVector3(const Vector3& v) const
{
	float x = v.x * value[0][0] + v.y * value[1][0] + v.z * value[2][0] + v.w * value[3][0];
	float y = v.x * value[0][1] + v.y * value[1][1] + v.z * value[2][1] + v.w * value[3][1];
	float z = v.x * value[0][2] + v.y * value[1][2] + v.z * value[2][2] + v.w * value[3][2];
	float w = v.x * value[0][3] + v.y * value[1][3] + v.z * value[2][3] + v.w * value[3][3];
	Vector3 returnValue(x, y, z);
	returnValue.w = w;
	return returnValue;
}

void Matrix::Identity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				value[i][j] = 1;
			else
				value[i][j] = 0;
		}
	}
}

void Matrix::Transpose()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			std::swap(value[i][j], value[j][i]);
		}
	}
}

Matrix Matrix::GenTranslateMatrix(const Vector3& v)
{
	Matrix m;
	m.Identity();
	m.value[3][0] = v.x;
	m.value[3][1] = v.y;
	m.value[3][2] = v.z;
	return m;
}

Matrix Matrix::GenRotationMatrix(const Vector3& rotAxis, float angle)
{
	Matrix m;
	return m;
}

Matrix Matrix::GenScaleMatrix(const Vector3& v)
{
	Matrix m;
	m.value[0][0] = v.x;
	m.value[1][1] = v.y;
	m.value[2][2] = v.z;
	return m;
}


//相机矩阵推导:http://blog.csdn.net/popy007/article/details/5120158
//DX版本实现：http://www.cnblogs.com/mikewolf2002/archive/2012/03/11/2390669.html
Matrix Matrix::GenCameraMatrix(const Vector3& eyePos, const Vector3& lookPos, const Vector3& upAxis)
{
	Vector3 lookDir = lookPos - eyePos;
	lookDir.Normalize();

	Vector3 rightDir = Vector3::Cross(upAxis, lookDir);
	rightDir.Normalize();

	Vector3 upDir = Vector3::Cross(lookDir, rightDir);
	upDir.Normalize();//?

	//构建一个坐标系，将vector转化到该坐标系，相当于对坐标系进行逆变换
	//C = RT,C^-1 = (RT)^-1 = (T^-1) * (R^-1),Translate矩阵逆矩阵直接对x,y,z取反即可；R矩阵为正交矩阵，故T^-1 = Transpose(T)
	//最终Camera矩阵为(T^-1) * Transpose(T)，此处可以直接给出矩阵乘法后的结果，减少运行时计算
	float transX = -Vector3::Dot(rightDir, eyePos);
	float transY = -Vector3::Dot(upDir, eyePos);
	float transZ = -Vector3::Dot(lookDir, eyePos);
	Matrix m;
	m.value[0][0] = rightDir.x;  m.value[0][1] = upDir.x;  m.value[0][2] = lookDir.x;  m.value[0][3] = 0;
	m.value[1][0] = rightDir.y;	 m.value[1][1] = upDir.y;  m.value[1][2] = lookDir.y;  m.value[1][3] = 0;
	m.value[2][0] = rightDir.z;  m.value[2][1] = upDir.z;  m.value[2][2] = lookDir.z;  m.value[2][3] = 0;
	m.value[3][0] = transX;		 m.value[3][1] = transY;   m.value[3][2] = transZ;	   m.value[3][3] = 1;
	return m;
}

void Matrix::Print()
{
	std::cout << "-----------------Matrix Begin--------------" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << "[" << value[i][j] << "]   ";
		}
		std::cout << std::endl;
	}
	std::cout << "-----------------Matrix End----------------" << std::endl;
}


