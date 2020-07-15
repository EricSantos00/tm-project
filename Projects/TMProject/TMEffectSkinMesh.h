#pragma once

class TMVector3;

class TMSkinMesh;

class TMObject;

struct LOOK_INFO
{
    unsigned __int16 Mesh0;
    unsigned __int16 Skin0;
    unsigned __int16 Mesh1;
    unsigned __int16 Skin1;
    unsigned __int16 Mesh2;
    unsigned __int16 Skin2;
    unsigned __int16 Mesh3;
    unsigned __int16 Skin3;
    unsigned __int16 Mesh4;
    unsigned __int16 Skin4;
    unsigned __int16 Mesh5;
    unsigned __int16 Skin5;
    unsigned __int16 Mesh6;
    unsigned __int16 Skin6;
    unsigned __int16 Mesh7;
    unsigned __int16 Skin7;
};

struct SANC_INFO
{
    char Sanc0;
    char Sanc1;
    char Sanc2;
    char Sanc3;
    char Sanc4;
    char Sanc5;
    char Sanc6;
    char Sanc7;
    char Legend0;
    char Legend1;
    char Legend2;
    char Legend3;
    char Legend4;
    char Legend5;
    char Legend6;
    char Legend7;
};

enum EEFFECT_ALPHATYPE
{
    EF_DEFAULT = 0x0,
    EF_BRIGHT = 0x1,
    EF_NONEBRIGHT = 0x2,
    EF_ALPHA = 0x3,
};

class TMEffectSkinMesh : public TMObject
{
public:
    TMEffectSkinMesh(int nSkinMeshType, TMVector3 vecStart, TMVector3 vecTarget, int nLevel, TMObject* pOwner);
    ~TMEffectSkinMesh();
    
    int InitObject(int bExpand);
    int Render();
    int FrameMove(unsigned int dwServerTime);
    void RestoreDeviceObjects();
    void InvalidateDeviceObjects();
    void InitPosition(float fX, float fY, float fZ);

public:
    LOOK_INFO m_stLookInfo;
    SANC_INFO m_stSancInfo;
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    EEFFECT_ALPHATYPE m_efAlphaType;
    int m_nMotionType;
    float m_fStartAngle;
    D3DCOLORVALUE m_StartColor;
    D3DCOLORVALUE m_EndColor;
    D3DCOLORVALUE m_color;
    int m_nFade;
    TMVector3 m_vecStartPos;
    TMVector3 m_vecTargetPos;
    int m_nLevel;
    float m_fAngle;
    unsigned int m_dwLastSpeedUp;
    LOOK_INFO m_stLookInfo2;
    TMSkinMesh* m_pSkinMesh2;
    int m_nSkinMeshType2;
    float m_fScale2;
    int m_bMirror;
};