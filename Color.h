/*******************************************************************
 * \file Color.h
 *
 * \author puppet_master
 * \date 2018/05/20
 * \https://blog.csdn.net/puppet_master
 * \颜色类实现
 *******************************************************************/
#pragma once
class Color
{
public:
	float r, g, b, a;
	Color(float cr, float cg, float cb, float ca);
	Color() {};
	~Color();

	Color operator + (const Color& right) const;
	Color operator - (const Color& right) const;
	Color operator * (const Color& right) const;
	Color operator * (float value) const;
	Color operator / (float value) const;
	static Color Lerp(const Color& left, const Color& right, float t);
	static Color white;
};

