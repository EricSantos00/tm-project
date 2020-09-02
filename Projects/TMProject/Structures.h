#pragma once

#include <math.h>

struct TMVector2
{
	float x;
	float y;

	float DistanceFrom(const TMVector2& target)
	{
		auto vTemp = *this - target;
		float length = (vTemp.x * vTemp.x) + (vTemp.y * vTemp.y);
		return (float)sqrt(length);
	}

	float DistanceFrom2(const TMVector2& target)
	{
		auto vTemp = *this - target;

		return ((vTemp.x * vTemp.x) + (vTemp.y * vTemp.y));
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

	TMVector2* operator+=(const TMVector2 other)
	{
		this->x = this->x + other.x;
		this->y = this->y + other.y;

		return this;
	}

	TMVector2* operator+=(const TMVector2* other)
	{
		this->x = this->x + other->x;
		this->y = this->y + other->y;

		return this;
	}

	TMVector2 operator-(const TMVector2& other)
	{
		TMVector2 ret;

		ret.x = x - other.x;
		ret.y = y - other.y;

		return ret;
	}

	TMVector2 operator+(const TMVector2& other)
	{
		TMVector2 ret;

		ret.x = x + other.x;
		ret.y = y + other.y;

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
	
	TMVector3 operator+(const TMVector3& other)
	{
		TMVector3 ret;

		ret.x = this->x + other.x;
		ret.y = this->y + other.y;
		ret.z = this->z + other.z;

		return ret;
	}

	TMVector3 operator*(const float value)
	{
		TMVector3 ret;

		ret.x = this->x * value;
		ret.y = this->y * value;
		ret.z = this->z * value;

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

	RDLVERTEX()
	{
		diffuse = 0;
		tu = 0.0f;
		tv = 0.0f;
	}
};

struct RDLVERTEX2
{
	TMVector3 position;
	unsigned int diffuse;
	float tu1;
	float tv1;
	float tu2;
	float tv2;
};

struct RDLNVERTEX2
{
	TMVector3 position;
	TMVector3 normal;
	unsigned int diffuse;
	float tu1;
	float tv1;
	float tu2;
	float tv2;
};

struct LOOK_INFO
{
	short Mesh0;
	short Skin0;
	short Mesh1;
	short Skin1;
	short Mesh2;
	short Skin2;
	short Mesh3;
	short Skin3;
	short Mesh4;
	short Skin4;
	short Mesh5;
	short Skin5;
	short Mesh6;
	short Skin6;
	short Mesh7;
	short Skin7;
};

struct SANC_INFO
{
	unsigned char Sanc0;
	unsigned char Sanc1;
	unsigned char Sanc2;
	unsigned char Sanc3;
	unsigned char Sanc4;
	unsigned char Sanc5;
	unsigned char Sanc6;
	unsigned char Sanc7;
	unsigned char Legend0;
	unsigned char Legend1;
	unsigned char Legend2;
	unsigned char Legend3;
	unsigned char Legend4;
	unsigned char Legend5;
	unsigned char Legend6;
	unsigned char Legend7;
};

struct HUMAN_LOOKINFO
{
	short FaceMesh;
	short FaceSkin;
	short HelmMesh;
	short HelmSkin;
	short CoatMesh;
	short CoatSkin;
	short PantsMesh;
	short PantsSkin;
	short GlovesMesh;
	short GlovesSkin;
	short BootsMesh;
	short BootsSkin;
	short RightMesh;
	short RightSkin;
	short LeftMesh;
	short LeftSkin;
};

struct ResourceDef
{
	char szString[48];
	int nNumber;
};

struct stMemo
{
	unsigned int dwColor;
	char szString[128];
};

struct stPlayTime
{
	char strAccount[16];
	int nServer;
	unsigned short nYear;
	unsigned short nMonth;
	unsigned short nDay;
	unsigned short nHour;
	unsigned short nMinute;
	unsigned short nPlayTime;
};

struct stCam
{
	float fHorizonAngle;
	float fVerticalAngle;
	float fWantLength;
	float fX;
	float fY;
};

struct stMobAni
{
	unsigned int dwTick;
	char cWhat;
	short sAni;
	IVector2 vecPos;
};

struct stDemoHuman
{
	int nFace;
	int Helm;
	int Body;
	int Mantua;
	int Right;
	int Left;
	int nSanc;
	int nMount;
	float fX;
	float fY;
	float fTX;
	float fTY;
	int nAngle;
	int nSpeed;
	int nHumanAni;
};

struct stDemoHuman2
{
	int nFace;
	int Helm;
	int Body;
	int Mantua;
	int Right;
	int Left;
	int nSanc;
	int nMount;
	int nX;
	int nY;
	int nAngle;
	int nSpeed;
};

struct stCurse
{
	char szOriginal[16];
	char szTrans[16];
};

struct stCurse_num
{
	stCurse* pCurseList;
	unsigned int dnum;
};

struct ObjectFileItem
{
	unsigned int dwObjType;
	TMVector2 vecPosition;
	float fHeight;
	float fAngle;
	int nTextureSetIndex;
	int nMaskIndex;
	float fScaleH;
	float fScaleV;
};

struct stMinimapPos
{
	int nX;
	int nY;
	int nCX;
	int nCY;
	unsigned int dwColor;
	char szTarget[32];
};

struct stTeleportPos
{
	int nX;
	int nY;
	int nPrice;
	char* szTarget;
};

struct stIDDis
{
	unsigned int dwID;
	int nLen;
};