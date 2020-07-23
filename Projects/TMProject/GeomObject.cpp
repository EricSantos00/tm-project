#include "pch.h"
#include "TMFont2.h"
#include "GeomObject.h"

GeomControl::GeomControl()
{
    eRenderType = RENDERCTRLTYPE::RENDER_IMAGE;
    nPosX = 0.0;
    nPosY = 0.0;
    nWidth = 0.0;
    nHeight = 0.0;
    fAngle = 0.0;
    fScale = 1.0f;
    dwColor = 0xFFAAAAAA;
    bVisible = 1;
    n3DObjIndex = 0;
    nTextureSetIndex = -1;
    nTextureIndex = 0;
    sLegend = 0;
    nLayer = -1;
    pFont = 0;
    m_pNextGeom = 0;
    dwBGColor = 0;
    strString[0] = 0;
    nMarkIndex = -1;
    nMarkLayout = 3;
    bClip = 0;

    //Those values weren't shown at decompilation, I've added by myself to remove related warnings
    fBottom = 0.0f;
    fLeft = 0.0f;
    fRight = 0.0f;
    fTop = 0.0f;
    m_fHeight = 0.0f;
    m_fWidth = 0.0f;
    nZ = 0;
    sSanc = 0;
}

GeomControl::GeomControl(RENDERCTRLTYPE ieRenderType, int inTextureSetIndex, float inPosX, float inPosY, float inWidth, float inHeight, int inLayer, unsigned int idwColor)
{
    eRenderType = ieRenderType;
    nPosX = inPosX;
    nPosY = inPosY;
    nWidth = inWidth;
    nHeight = inHeight;
    fAngle = 0.0;
    fScale = 1.0f;
    dwColor = idwColor;
    bVisible = 1;
    n3DObjIndex = 0;
    nTextureSetIndex = inTextureSetIndex;
    nTextureIndex = 0;
    sLegend = 0;
    sSanc = 0;
    nLayer = -1;
    pFont = 0;
    m_pNextGeom = 0;
    dwBGColor = 0;
    strString[0] = 0;
    nMarkIndex = -1;
    nMarkLayout = 3;
    bClip = 0;

    //Those values weren't shown at decompilation, I've added by myself to remove related warnings
    fBottom = 0.0f;
    fLeft = 0.0f;
    fRight = 0.0f;
    fTop = 0.0f;
    m_fHeight = 0.0f;
    m_fWidth = 0.0f;
    nZ = 0;
}
