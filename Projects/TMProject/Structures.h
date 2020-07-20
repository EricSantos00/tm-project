#pragma once

#include <math.h>

struct TMVector2
{
	float x;
	float y;

	float DistanceFrom(const TMVector2& target)
	{
		return (float)sqrt(DistanceFrom2(target));
	}

	float DistanceFrom2(const TMVector2& target)
	{
		TMVector2 temp = *this;
		TMVector2 result = temp - target;

		return (float)((float)(temp.x * temp.y) + (float)(temp.y * temp.y));
	}

	TMVector2(float iX, float iY)
	{
		x = iX;
		y = iY;
	}
	TMVector2()
	{
		x = 0;
		y = 0;
	}

	TMVector2* operator=(TMVector2* other)
	{
		*this = *other;
		return this;
	}

	TMVector2 operator*(const float value)
	{
		TMVector2 ret;
		ret.x = x * value;
		ret.y = y * value;

		return ret;
	}

	TMVector2 operator/(const float value)
	{
		TMVector2 ret;
		ret.x = x / value;
		ret.y = y / value;

		return ret;
	}

	TMVector2* operator+=(TMVector2* other)
	{
		x = x + other->x;
		y = y + other->y;

		return this;
	}

	TMVector2 operator-(const TMVector2& other)
	{
		TMVector2 ret;

		ret.x = x - other.x;
		ret.y = y - other.y;

		return ret;
	}
};

struct TMVector3
{
	float x;
	float y;
	float z;

	float Length()
	{
		return (float)(sqrt((float)((x * x) + (y * y) + (z * z))));
	}

	float DistanceFrom(const TMVector3& target)
	{
		TMVector3 temp = *this;
		TMVector3 result = temp - target;

		return result.Length();
	}

	TMVector3(float iX, float iY, float iZ)
	{
		x = iX;
		y = iY;
		z = iZ;
	}
	TMVector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	TMVector3* operator=(TMVector3* other)
	{
		*this = *other;
		return this;
	}

	TMVector3* operator*=(float value)
	{
		x = x * value;
		y = y * value;
		z = z * value;

		return this;
	}

	TMVector3 operator-(const TMVector3& other)
	{
		TMVector3 ret;

		ret.x = this->x - other.x;
		ret.y = this->y - other.y;
		ret.z = this->z - other.z;

		return ret;
	}

	TMVector3 operator/(const float value)
	{
		TMVector3 ret;

		ret.x = x / value;
		ret.y = y / value;
		ret.z = z / value;

		return ret;
	}
};

struct IVector2
{
	int x;
	int y;

	IVector2(int iX, int iY)
	{
		x = iX;
		y = iY;
	}

	IVector2()
	{
		x = 0;
		y = 0;
	}

	IVector2* operator=(IVector2* other)
	{
		*this = *other;
		return this;
	}
};

struct RDTLVERTEX2
{
	TMVector3 position;
	float rhw;
	unsigned int diffuse;
	float tu1;
	float tv1;
	float tu2;
	float tv2;
};

struct RDTLVERTEX
{
	TMVector3 position;
	float rhw;
	unsigned int diffuse;
	float tu;
	float tv;
};

struct RDLVERTEX
{
	TMVector3 position;
	unsigned int diffuse;
	float tu;
	float tv;
};