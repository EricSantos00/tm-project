#pragma once

#include "TreeNode.h"
#include "Structures.h"

struct FileTileInfo
{
    char cHeight;
    char byTileIndex;
    char byTileCoord;
    char byBackTileIndex;
    char byBackTileCoord;
    unsigned int dwColor;
};

class TMSea;
class TMGround : public TreeNode
{
public:
    TMGround();
    ~TMGround();

    void RestoreDeviceObjects() override;
    void SetPos(int nX, int nY);
    int Attach(TMGround* pGround);
    int LoadTileMap(const char* szFileName);
    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;
    D3DXVECTOR3 GetPickPos();
    float GetHeight(TMVector2 vecPosition);
    int GetMask(TMVector2 vecPosition);
    D3DCOLORVALUE GetColor(TMVector2 vecPosition);
    int GetTileType(TMVector2 vecPosition);
    void SetColor(TMVector2 vecPosition, unsigned int dwColor);
    TMVector3 GetNormalInGround(int nX, int nY);
    int SetMiniMapData();
    void SetAttatchEnable(int nX, int nY);
    int IsInWater(TMVector2 vecPosition, float fHeight, float* pfWaterHeight);
    float GetWaterHeight(TMVector2 vecPosition, float* pfWaterHeight);

public:
    static float TileCoordList[8][4][2];
    static float BackTileCoordList[32][4][2];
    static int m_nCheckSum[64][32];
    static int m_bFirst;
    static float m_fMiniMapScale;

public:
    char m_MapName[128];
    unsigned int m_dwLastEffectTime;
    unsigned int m_dwServertime;
    TMGround* m_pLeftGround;
    TMGround* m_pRightGround;
    TMGround* m_pUpGround;
    TMGround* m_pDownGround;
    int m_bVisible;
    int m_bWire;
    int m_bDungeon;
    int m_nMiniMapPos;
    FileTileInfo m_TileMapData[4096];
    char m_pMaskData[128][128];
    char m_pVAttrData[128][128];
    TMVector3 m_TileNormalVector[4096];
    D3DMATERIAL9 m_materials;
    RDLNVERTEX2 m_vertex[4];
    RDLVERTEX m_vertexVoodoo[4];
    int m_nOptTexture[512];
    IVector2 m_vecOffsetIndex;
    TMVector2 m_vecOffset;
    char m_cLeftEnable;
    char m_cRightEnable;
    char m_cUpEnable;
    char m_cDownEnable;
    TMSea* m_pSeaList[10];
    int m_nSeaIndex;
    float m_fEffHeight;
    TMVector2 m_vecEffset;
    unsigned int m_dwEffStart;
};