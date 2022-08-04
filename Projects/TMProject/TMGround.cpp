#include "pch.h"
#include "TMSea.h"
#include "TMScene.h"
#include "TMGlobal.h"
#include "TMHuman.h"
#include "TMLog.h"
#include "TMGround.h"
#include "TMCamera.h"
#include "TMEffectBillBoard.h"
#include "TMSkillFire.h"
#include "TMUtil.h"

float TMGround::TileCoordList[8][4][2] =
{
  { {  0.0f,  0.0f }, {  0.0f,  1.0f }, {  1.0f,  0.0f }, {  1.0f,  1.0f } },
  { {  1.0f,  0.0f }, {  0.0f,  0.0f }, {  1.0f,  1.0f }, {  0.0f,  1.0f } },
  { {  1.0f,  1.0f }, {  1.0f,  0.0f }, {  0.0f,  1.0f }, {  0.0f,  0.0f } },
  { {  0.0f,  1.0f }, {  1.0f,  1.0f }, {  0.0f,  0.0f }, {  1.0f,  0.0f } },
  { {  0.0f,  0.0f }, {  1.0f,  0.0f }, {  0.0f,  1.0f }, {  1.0f,  1.0f } },
  { {  0.0f,  1.0f }, {  0.0f,  0.0f }, {  1.0f,  1.0f }, {  1.0f,  0.0f } },
  { {  1.0f,  1.0f }, {  0.0f,  1.0f }, {  1.0f,  0.0f }, {  0.0f,  0.0f } },
  { {  1.0f,  0.0f }, {  1.0f,  1.0f }, {  0.0f,  0.0f }, {  0.0f,  1.0f } }
};

float TMGround::BackTileCoordList[32][4][2] =
{
  { {  0.0f,  0.0f }, {  0.0f,  0.5f }, {  0.5f,  0.0f }, {  0.5f,  0.5f } },
  { {  1.0f,  0.0f }, {  0.5f,  0.0f }, {  1.0f,  0.5f }, {  0.5f,  0.5f } },
  { {  1.0f,  1.0f }, {  1.0f,  0.5f }, {  0.5f,  1.0f }, {  0.5f,  0.5f } },
  { {  0.0f,  1.0f }, {  0.5f,  1.0f }, {  0.0f,  0.5f }, {  0.5f,  0.5f } },
  { {  0.0f,  0.0f }, {  0.5f,  0.0f }, {  0.0f,  0.5f }, {  0.5f,  0.5f } },
  { {  0.0f,  1.0f }, {  0.0f,  0.5f }, {  0.5f,  1.0f }, {  0.5f,  0.5f } },
  { {  1.0f,  1.0f }, {  0.5f,  1.0f }, {  1.0f,  0.5f }, {  0.5f,  0.5f } },
  { {  1.0f,  0.0f }, {  1.0f,  0.5f }, {  0.5f,  0.0f }, {  0.5f,  0.5f } },
  { {  0.0f,  0.5f }, {  0.0f,  1.0f }, {  0.5f,  0.5f }, {  0.5f,  1.0f } },
  { {  0.5f,  0.0f }, {  0.0f,  0.0f }, {  0.5f,  0.5f }, {  0.0f,  0.5f } },
  { {  1.0f,  0.5f }, {  1.0f,  0.0f }, {  0.5f,  0.5f }, {  0.5f,  0.0f } },
  { {  0.5f,  1.0f }, {  1.0f,  1.0f }, {  0.5f,  0.5f }, {  1.0f,  0.5f } },
  { {  0.5f,  0.0f }, {  1.0f,  0.0f }, {  0.5f,  0.5f }, {  1.0f,  0.5f } },
  { {  0.0f,  0.5f }, {  0.0f,  0.0f }, {  0.5f,  0.5f }, {  0.5f,  0.0f } },
  { {  0.5f,  1.0f }, {  0.0f,  1.0f }, {  0.5f,  0.5f }, {  0.0f,  0.5f } },
  { {  1.0f,  0.5f }, {  1.0f,  1.0f }, {  0.5f,  0.5f }, {  0.5f,  1.0f } },
  { {  0.5f,  0.0f }, {  0.5f,  0.5f }, {  1.0f,  0.0f }, {  1.0f,  0.5f } },
  { {  1.0f,  0.5f }, {  0.5f,  0.5f }, {  1.0f,  1.0f }, {  0.5f,  1.0f } },
  { {  0.5f,  1.0f }, {  0.5f,  0.5f }, {  0.0f,  1.0f }, {  0.0f,  0.5f } },
  { {  0.0f,  0.5f }, {  0.5f,  0.5f }, {  0.0f,  0.0f }, {  0.5f,  0.0f } },
  { {  0.0f,  0.5f }, {  0.5f,  0.5f }, {  0.0f,  1.0f }, {  0.5f,  1.0f } },
  { {  0.5f,  1.0f }, {  0.5f,  0.5f }, {  1.0f,  1.0f }, {  1.0f,  0.5f } },
  { {  1.0f,  0.5f }, {  0.5f,  0.5f }, {  1.0f,  0.0f }, {  0.5f,  0.0f } },
  { {  0.5f,  0.0f }, {  0.5f,  0.5f }, {  0.0f,  0.0f }, {  0.0f,  0.5f } },
  { {  0.5f,  0.5f }, {  0.5f,  1.0f }, {  1.0f,  0.5f }, {  1.0f,  1.0f } },
  { {  0.5f,  0.5f }, {  0.0f,  0.5f }, {  0.5f,  1.0f }, {  0.0f,  1.0f } },
  { {  0.5f,  0.5f }, {  0.5f,  0.0f }, {  0.0f,  0.5f }, {  0.0f,  0.0f } },
  { {  0.5f,  0.5f }, {  1.0f,  0.5f }, {  0.5f,  0.0f }, {  1.0f,  0.0f } },
  { {  0.5f,  0.5f }, {  1.0f,  0.5f }, {  0.5f,  1.0f }, {  1.0f,  1.0f } },
  { {  0.5f,  0.5f }, {  0.5f,  0.0f }, {  1.0f,  0.5f }, {  1.0f,  0.0f } },
  { {  0.5f,  0.5f }, {  0.0f,  0.5f }, {  0.5f,  0.0f }, {  0.0f,  0.0f } },
  { {  0.5f,  0.5f }, {  0.5f,  1.0f }, {  0.0f,  0.5f }, {  0.0f,  1.0f } }
};

int TMGround::m_nCheckSum[64][32] =
{
  {
    -1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  }
};

int TMGround::m_bFirst = 1;
float TMGround::m_fMiniMapScale = 0.60f;

TMGround::TMGround()
    : TreeNode(0)
{
    m_vecOffsetIndex = IVector2{};
    m_vecEffset = TMVector2{};

    m_pLeftGround = 0;
    m_pRightGround = 0;
    m_pUpGround = 0;
    m_pDownGround = 0;
    m_nSeaIndex = 0;
    m_bVisible = 1;
    m_bDungeon = 0;
    m_bWire = 0;
    m_dwLastEffectTime = 0;
    m_dwServertime = 0;
    m_cLeftEnable = 0;
    m_cRightEnable = 0;
    m_cUpEnable = 0;
    m_cDownEnable = 0;
    m_fEffHeight = 2.0f;
    m_dwEffStart = 0;

    // this code is to supress warnings
    memset(&m_MapName, 0, sizeof m_MapName);
    memset(&m_TileMapData, 0, sizeof m_TileMapData);

    for (int i = 0; i < 4; ++i)
    {
        m_vertex[i].diffuse = 0x00FFFFFF;
        m_vertexVoodoo[i].diffuse = 0x00FFFFFF;
    }

    for (int i = 0; i < 128; ++i)
    {
        memset(&m_pMaskData[i], 0, sizeof m_pMaskData[i]);
        memset(&m_pVAttrData[i], 0, sizeof m_pVAttrData[i]);
    }

    for (int i = 0; i < 10; ++i)
        m_pSeaList[i] = 0;

    if (TMGround::m_bFirst == 1)
    {
        FILE* pFile = nullptr;
        fopen_s(&pFile, "cdata.bin", "rb");

        if (pFile)
        {
            fread(&TMGround::m_nCheckSum, sizeof m_nCheckSum, 1u, pFile);

            int nCDataCheckSum = 0;
            for (int k = 0; k < 64; ++k)
                for (int j = 0; j < 32; ++j)
                    nCDataCheckSum += 8 * k + 4 * m_nCheckSum[j][j] * 16 * j;

            if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD && nCDataCheckSum != 5855606140)
            {
                fclose(pFile);

                LOG_WRITELOG("DataFile Error\r\n");
                MessageBoxA(g_pApp->m_hWnd, "DataFile Error.", "File Error", 0);
                PostMessageA(g_pApp->m_hWnd, WM_CLOSE, 0, 0);

                return;
            }

            fclose(pFile);
            m_bFirst = 0;
        }
        else
        {
            LOG_WRITELOG("DataFile NotFound");

            if (!g_pCurrentScene->m_bCriticalError)
                g_pCurrentScene->LogMsgCriticalError(4, 0, 0, 0, 0);

            g_pCurrentScene->m_bCriticalError = 1;
            return;
        }
    }

    SetPos(0, 0);
    return;
}

TMGround::~TMGround()
{
}

void TMGround::RestoreDeviceObjects()
{
    SetMiniMapData();
}

void TMGround::SetPos(int nX, int nY)
{
    m_vecOffsetIndex.x = nX;
    m_vecOffsetIndex.y = nY;

    m_vecOffset.x = (m_vecOffsetIndex.x * 2.0f) * 64.0f;
    m_vecOffset.y = (m_vecOffsetIndex.y * 2.0f) * 64.0f;

    if (nY <= 25)
    {
        if (nX >= 8 && nY <= 12 && nY >= 11 && nY <= 14)
        {
            m_bDungeon = 3;
            RenderDevice::m_bDungeon = 3;
        }
        else if (nX > 1 && nX < 11 && nY < 5)
        {
            m_bDungeon = 4;
            RenderDevice::m_bDungeon = 4;
        }
        else if (nX >= 26 && nX <= 30 && nY >= 8 && nY <= 12)
        {
            m_bDungeon = 5;
            RenderDevice::m_bDungeon = 5;
        }
        else
        {
            m_bDungeon = 0;
            RenderDevice::m_bDungeon = 0;
        }
    }
    else
    {
        if (nX < 16 && nX > 8 && nY > 25)
        {
            m_bDungeon = 2;
            RenderDevice::m_bDungeon = 2;
        }
        else
        {
            m_bDungeon = 1;
            RenderDevice::m_bDungeon = 1;
        }
    }
}

int TMGround::Attach(TMGround* pGround)
{
    if (!pGround)
        return 0;

    m_pLeftGround = 0;
    m_pRightGround = 0;
    m_pUpGround = 0;
    m_pDownGround = 0;

    if (pGround->m_vecOffsetIndex.x == m_vecOffsetIndex.x + 1)
    {
        m_pRightGround = pGround;
        m_pRightGround->m_pLeftGround = this;

        for (int i = 0; i < 64; ++i)
        {
            pGround->m_TileMapData[64 * i].cHeight = m_TileMapData[(i << 6) + 63].cHeight;
            pGround->m_TileMapData[64 * i].dwColor = m_TileMapData[(i << 6) + 63].dwColor;

            pGround->m_TileNormalVector[64 * i] = m_TileNormalVector[64 * i + 63];
        }

        m_nMiniMapPos = 0;
        m_pRightGround->m_nMiniMapPos = 1;
        return 1;
    }
    if (pGround->m_vecOffsetIndex.x == m_vecOffsetIndex.x - 1)
    {
        m_pLeftGround = pGround;
        m_pLeftGround->m_pRightGround = this;

        for (int i = 0; i < 64; ++i)
        {
            m_TileMapData[64 * i].cHeight = pGround->m_TileMapData[(i << 6) + 63].cHeight;
            m_TileMapData[64 * i].dwColor = pGround->m_TileMapData[(i << 6) + 63].dwColor;

           m_TileNormalVector[64 * i] = pGround->m_TileNormalVector[64 * i + 63];
        }

        m_nMiniMapPos = 1;
        m_pLeftGround->m_nMiniMapPos = 0;
        return 1;
    }
    if (pGround->m_vecOffsetIndex.y == m_vecOffsetIndex.y + 1)
    {
        m_pDownGround = pGround;
        m_pDownGround->m_pUpGround = this;

        for (int i = 0; i < 64; ++i)
        {
            pGround->m_TileMapData[i].cHeight = m_TileMapData[i + 4032].cHeight;
            pGround->m_TileMapData[i].dwColor = m_TileMapData[i + 4032].dwColor;

            pGround->m_TileNormalVector[i] = m_TileNormalVector[i + 4032];
        }

        m_nMiniMapPos = 0;
        m_pDownGround->m_nMiniMapPos = 2;
        return 1;
    }
    if (pGround->m_vecOffsetIndex.y == m_vecOffsetIndex.y - 1)
    {
        m_pUpGround = pGround;
        m_pUpGround->m_pDownGround = this;

        for (int i = 0; i < 64; ++i)
        {
            m_TileMapData[i].cHeight = pGround->m_TileMapData[i + 4032].cHeight;
            m_TileMapData[i].dwColor = pGround->m_TileMapData[i + 4032].dwColor;

            m_TileNormalVector[i] = pGround->m_TileNormalVector[i + 4032];
        }

        m_nMiniMapPos = 2;
        m_pUpGround->m_nMiniMapPos = 0;
        return 1;
    }

    return 0;
}

int TMGround::LoadTileMap(const char* szFileName)
{
    FILE* fp = nullptr;
    fopen_s(&fp, szFileName, "rb");

    if (fp)
    {
        int byNameLen = 0;
        fread(&byNameLen, 1u, 1u, fp);

       //  added to supress warning
        if (byNameLen > 128)
            byNameLen = 128;

        fread(m_MapName, 1u, byNameLen, fp);

        m_MapName[byNameLen] = '\0';

        int bPosX = 0;
        int bPosY = 0;
        fread(&bPosX, 1, 1, fp);
        fread(&bPosY, 1, 1, fp);

        SetPos(bPosX, bPosY);
        SetAttatchEnable(bPosX, bPosY);

        fread(m_TileMapData, 12, 4096, fp);
        fclose(fp);

        if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
        {
            int nCheckSum = 0;
            int nCheckSize = 49152;
            auto pCheck = (char*)m_TileMapData;

            for (int i = 0; i < nCheckSize; nCheckSum += pCheck[i++])
                ;

            if (m_nCheckSum[bPosY][bPosX] != nCheckSum + bPosX * bPosY)
            {
                LOG_WRITELOG("CheckSum Error: %d,%d m_nCheckSum=%d nCheckSum= %d\r\n",
                    bPosX, bPosY, m_nCheckSum[bPosY][bPosX], nCheckSum + bPosX * bPosY);

                if (!g_pCurrentScene->m_bCriticalError)
                    g_pCurrentScene->LogMsgCriticalError(5, 0, 0, 0, 0);

                g_pCurrentScene->m_bCriticalError = 1;
                return 0;
            }
        }

        for (int nY = 1; nY < 63; ++nY)
        {
            for (int nX = 1; nX < 63; ++nX)
            {
                m_TileNormalVector[nX + (nY << 6)] = GetNormalInGround(nX, nY);
            }
        }

        for (int nNoIndex = 0; nNoIndex < 64; ++nNoIndex)
        {
            m_TileNormalVector[64 * nNoIndex] = m_TileNormalVector[64 * nNoIndex + 1];
            m_TileNormalVector[(nNoIndex << 6) + 63] = m_TileNormalVector[64 * nNoIndex + 62];
        }

        for (int nNoIndex = 0; nNoIndex < 64; ++nNoIndex)
        {
            m_TileNormalVector[nNoIndex] = m_TileNormalVector[nNoIndex + 64];
            m_TileNormalVector[nNoIndex + 4032] = m_TileNormalVector[nNoIndex + 3968];
        }

        memset(&m_materials, 0, sizeof m_materials);
        m_materials.Diffuse.r = 1.0f;
        m_materials.Diffuse.g = 1.0f;
        m_materials.Diffuse.b = 1.0f;

        m_materials.Specular = m_materials.Diffuse;
        m_materials.Power = 0.0f;

        m_materials.Emissive.r = 0.3f;
        m_materials.Emissive.g = 0.3f;
        m_materials.Emissive.b = 0.3f;

        if (g_pDevice->m_bVoodoo == 1)
        {
            m_materials.Emissive.r = 0.2f;
            m_materials.Emissive.g = 0.2f;
            m_materials.Emissive.b = 0.2f;
        }

        for (int nY = 0; nY < 64; ++nY)
            m_TileMapData[64 * nY].cHeight = m_TileMapData[(nY << 6) + 1].cHeight;

        for (int j = 0; j < 64; ++j)
            m_TileMapData[j].cHeight = m_TileMapData[j + 64].cHeight;

        for (int nY = 0; nY < 64; ++nY)
        {
            for (int j = 0; j < 64; ++j)
            {
                float f1 = 0.0f;
                float f2 = 0.0f;
                float f3 = 0.0f;
                float f4 = 0.0f;

                f1 = m_TileMapData[j + (nY << 6)].cHeight;
                if (nY < 62)
                    f3 = m_TileMapData[j + ((nY + 1) << 6)].cHeight;
                else
                    f3 = m_TileMapData[j + (nY << 6)].cHeight;

                if (j < 62)
                {
                    f2 = m_TileMapData[j + (nY << 6) + 1].cHeight;

                    if (nY >= 62)
                        f4 = m_TileMapData[j + (nY << 6) + 1].cHeight;
                    else
                        f4 = m_TileMapData[j + ((nY + 1) << 6) + 1].cHeight;
                }
                else
                {
                    f2 = m_TileMapData[j + (nY << 6)].cHeight;

                    if (nY >= 62)
                        f4 = m_TileMapData[j + (nY << 6)].cHeight;
                    else
                        f4 = m_TileMapData[j + ((nY + 1) << 6)].cHeight;
                }

                float fCenter = (((f1 + f2) + f3) + f4) / 4.0f;
                m_pMaskData[2 * nY][2 * j] = static_cast<char>((f1 + fCenter) / 2.0f);
                m_pMaskData[2 * nY][2 * j + 1] = static_cast<char>((f2 + fCenter) / 2.0f);
                m_pMaskData[2 * nY + 1][2 * j] = static_cast<char>((f3 + fCenter) / 2.0f);
                m_pMaskData[2 * nY + 1][2 * j + 1] = static_cast<char>((f4 + fCenter) / 2.0f);
            }
        }

        if (!m_cUpEnable)
        {
            for (int X = 0; X < 128; ++X)
            {
                for (int Y = 0; Y < 15; ++Y)
                    m_pMaskData[Y][X] = 127;
            }
        }

        if (!m_cDownEnable)
        {
            for (int k = 0; k < 128; ++k)
            {
                for (int l = 114; l < 128; ++l)
                    m_pMaskData[l][k] = 127;
            }
        }
        
        if (!m_cLeftEnable)
        {
            for (int m = 0; m < 128; ++m)
            {
                for (int n = 0; n < 15; ++n)
                    m_pMaskData[m][n] = 127;
            }
        }

        if (!m_cRightEnable)
        {
            for (int ii = 0; ii < 128; ++ii)
            {
                for (int jj = 114; jj < 128; ++jj)
                    m_pMaskData[ii][jj] = 127;
            }
        }

        if (m_cLeftEnable == 1 && m_cDownEnable == 1)
        {
            for (int kk = 0; kk < 16; ++kk)
            {
                for (int ll = 113; ll < 128; ++ll)
                    m_pMaskData[ll][kk] = 127;
            }
        }
        
        if (m_cLeftEnable == 1 && m_cUpEnable == 1)
        {
            for (int mm = 0; mm < 16; ++mm)
            {
                for (int nn = 0; nn < 16; ++nn)
                    m_pMaskData[nn][mm] = 127;
            }
        }
        
        if (m_cRightEnable == 1 && m_cDownEnable == 1)
        {
            for (int i1 = 113; i1 < 128; ++i1)
            {
                for (int i2 = 113; i2 < 128; ++i2)
                    m_pMaskData[i2][i1] = 127;
            }
        }
        
        if (m_cRightEnable == 1 && m_cUpEnable == 1)
        {
            for (int i3 = 113; i3 < 128; ++i3)
            {
                for (int i4 = 0; i4 < 16; ++i4)
                    m_pMaskData[i4][i3] = 127;
            }
        }

        return true;
    }
    else
        LOG_WRITELOG(">> Fail to Load TileMap : %s\r\n", szFileName);

    return 0;
}

int TMGround::Render()
{  
    if (g_bHideBackground)
        return 0;

    if (!m_bVisible)
        return 1;

    TMCamera* pCamera = g_pObjectManager->m_pCamera;
    if (pCamera->m_fVerticalAngle > 0.4f)
        return 1;

    if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
        return 1;

    int nXList[3]{};
    int nYList[3]{};
    unsigned int dwColor[4]{};
    float fX[4]{};
    float fY[4]{};

    D3DXVECTOR3 vTemp;
    D3DXVECTOR3 vPosTransformed;
    D3DXMATRIX matScale;
    D3DXMATRIX matPos;

    D3DXMatrixScaling(&matScale, 2.0f, 0.1f, 2.0f);
    D3DXMatrixTranslation(&matPos, m_vecOffset.x, 0, m_vecOffset.y);
    D3DXMatrixMultiply(&matScale, &g_pDevice->m_matWorld, &matScale);
    D3DXMatrixMultiply(&matScale, &matScale, &matPos);

    g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLD, &matScale);

    if (m_bWire == 1)
        g_pDevice->SetRenderState(D3DRS_FILLMODE, 2);

    TMVector3 vecCam = pCamera->m_cameraPos;

    int nCamPosX = ((int)(vecCam.x - m_vecOffset.x) / 2);
    int nCamPosY = ((int)(vecCam.z - m_vecOffset.y) / 2);

    g_pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, 3);

    if (g_pDevice->m_bVoodoo == 1)
    {
        g_pDevice->SetRenderState(D3DRS_COLORVERTEX, 1);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6);
    }
    else
    {
        g_pDevice->SetRenderState(D3DRS_COLORVERTEX, 1);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
        
        if (m_bDungeon && m_bDungeon != 3 && m_bDungeon != 4)
            g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, 1);
        else
            g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, 4);
        
        g_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
    }

    g_pDevice->m_pd3dDevice->SetMaterial(&m_materials);

    int nClipIndex = 15;
    if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_DEMO)
        nClipIndex = 18;

    int nMinClipIndex = 0;

    if (fabsf(g_pObjectManager->m_pCamera->m_fVerticalAngle) > 1.0f)
        nClipIndex = (int)((pCamera->m_fSightLength * 1.5f) + 8.0f);

    nMinClipIndex = nClipIndex / 3;
    
    int nMinX = nCamPosX - nMinClipIndex;
    int nMinY = nCamPosY - nMinClipIndex;
    int nMaxX = nClipIndex + nCamPosX;
    int nMaxY = nClipIndex + nCamPosY;

    if (RenderDevice::m_bDungeon >= 0 || g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELECT_SERVER || g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_DEMO)
    {
        int nLen = (int)(pCamera->m_fSightLength + 1.0f);

        if ((RenderDevice::m_bDungeon == 2
            || RenderDevice::m_bDungeon == 3
            || RenderDevice::m_bDungeon == 4
            || !RenderDevice::m_bDungeon
            || RenderDevice::m_bDungeon == 4)
            && g_pObjectManager->m_pCamera->m_fVerticalAngle > -0.69999999f)
        {
            nLen = 13;
        }

        if (nLen < 6)
            nLen = 6;

        nLen += 2; //??? pqp

        if ((int)vecCam.x >> 7 > 26
            && (int)vecCam.x >> 7 < 31
            && (int)vecCam.z >> 7 > 20
            && (int)vecCam.z >> 7 < 25)
        {
            if (g_pObjectManager->m_pCamera->m_fVerticalAngle > -0.60000002f)
            {
                nLen += 10;
            }
            else if (g_pObjectManager->m_pCamera->m_fVerticalAngle > -0.66000003f)
            {
                nLen += 4;
            }
            else if (g_pObjectManager->m_pCamera->m_fVerticalAngle > -0.68000001f)
            {
                nLen += 3;
            }
        }
        else if (g_pObjectManager->m_pCamera->m_fVerticalAngle > -0.60000002f)
            nLen += 3;

        float fcos = cosf(pCamera->m_fHorizonAngle);
        float fsin = sinf(pCamera->m_fHorizonAngle);
        nXList[0] = nCamPosX;
        nYList[0] = nCamPosY;
        nXList[1] = nCamPosX + (int)(nLen * fcos);
        nYList[1] = nCamPosY + (int)(nLen * fsin);
        nXList[2] = (nXList[1] + nCamPosX) / 2;
        nYList[2] = (nYList[1] + nCamPosY) / 2;
        nMinX = nXList[2] - nLen;
        nMinY = nYList[2] - nLen;
        nMaxX = nLen + nXList[2];
        nMaxY = nLen + nYList[2];
    }

    int nTickX = 1, nTickY = 1;
    for (int nY = nMinY; nY < nMaxY; ++nY)
    {
        if (nY >= 0 && nY <= 63)
        {
            for (int nX = nMinX; nX < nMaxX; ++nX)
            {
                if (nX < 0 || nX > 63)
                    continue;

                nTickX = 1;
                nTickY = 1;

                if (nCamPosX % 2)
                {
                    if (std::abs(nX - nCamPosX) > 17)
                    {
                        if (std::abs(nX - nCamPosX) % 2)
                            continue;

                        nTickX = 2;
                    }
                }
                else
                {
                    if (std::abs(nX - nCamPosX) > 16)
                    {
                        if (!(std::abs(nX - nCamPosX) % 2))
                            continue;

                        nTickX = 2;
                    }
                }

                if (nCamPosY % 2)
                {
                    if (std::abs(nY - nCamPosY) > 17)
                    {
                        if (std::abs(nY - nCamPosY) % 2 == 1)
                            continue;

                        nTickY = 2;
                    }
                }
                else
                {
                    if (std::abs(nY - nCamPosY) > 16)
                    {
                        if (!(std::abs(nY - nCamPosY) % 2))
                            continue;

                        nTickY = 2;
                    }
                }

                char bCoordIndex = m_TileMapData[nX + (nY << 6)].byTileCoord;
                char bCoordBackIndex = m_TileMapData[nX + (nY << 6)].byBackTileCoord;
                int nTexIndex = (unsigned char)m_TileMapData[nX + (nY << 6)].byTileIndex + 10;

                if (g_pDevice->m_bVoodoo == 1)
                {
                    // TODO: THIS CODE NEED TO BE REVIEW =)
                    for (int nVertexIndex = 0; nVertexIndex < 4; ++nVertexIndex)
                    {
                        m_vertexVoodoo[nVertexIndex].tu = TMGround::TileCoordList[(unsigned char)bCoordIndex][nVertexIndex][0];
                        m_vertexVoodoo[nVertexIndex].tv = TMGround::TileCoordList[(unsigned char)bCoordIndex][nVertexIndex][1];
                    }

                    dwColor[0] = m_TileMapData[nX + (nY << 6)].dwColor;
                    dwColor[1] = m_TileMapData[nX + ((nTickY + nY) << 6)].dwColor;
                    dwColor[2] = m_TileMapData[(nY << 6) + nTickX + nX].dwColor;
                    dwColor[3] = m_TileMapData[((nTickY + nY) << 6) + nTickX + nX].dwColor;

                    for (int i = 0; i < 4; i++)
                    {
                        auto fR = static_cast<float>(WYDCOLOR_RED(dwColor[i])) / 256.0f;
                        auto fG = static_cast<float>(WYDCOLOR_GREEN(dwColor[i])) / 256.0f;
                        auto fB = static_cast<float>(WYDCOLOR_BLUE(dwColor[i])) / 256.0f;

                        D3DXCOLOR color1 = D3DXCOLOR();
                        color1.r = fR;
                        color1.g = fG;
                        color1.b = fB;

                        D3DXCOLOR color2 = D3DXCOLOR();
                        color2.r = g_pDevice->m_colorLight.r * 0.40000001f;
                        color2.g = g_pDevice->m_colorLight.g * 0.40000001f;
                        color2.b = g_pDevice->m_colorLight.b * 0.40000001f;

                        D3DXCOLOR RetColor = D3DXCOLOR();
                        D3DXColorLerp(&RetColor, &color1, &color2, 0.69999999f);

                        m_vertexVoodoo[i].diffuse = (unsigned int)(RetColor.b * 256.0f) | ((unsigned int)(RetColor.g * 256.0f) << 8) | ((unsigned int)(RetColor.r * 256.0f) << 16);
                    }
                    if (nX < 63 && nY < 63)
                    {
                        m_vertex[0].diffuse = m_TileMapData[nX + (nY << 6)].dwColor;
                        m_vertex[1].diffuse = m_TileMapData[nX + ((nTickY + nY) << 6)].dwColor;
                        m_vertex[2].diffuse = m_TileMapData[(nY << 6) + nTickX + nX].dwColor;
                        m_vertex[3].diffuse = m_TileMapData[((nTickY + nY) << 6) + nTickX + nX].dwColor;

                        m_vertexVoodoo[0].position = TMVector3((float)nX, (float)m_TileMapData[nX + (nY << 6)].cHeight, (float)nY);
                        m_vertexVoodoo[1].position = TMVector3((float)nX, (float)m_TileMapData[nX + ((nTickY + nY) << 6)].cHeight, (float)(nTickY + nY));
                        m_vertexVoodoo[2].position = TMVector3((float)(nTickX + nX), (float)m_TileMapData[(nY << 6) + nTickX + nX].cHeight, (float)nY);
                        m_vertexVoodoo[3].position = TMVector3((float)(nTickX + nX), (float)m_TileMapData[((nTickY + nY) << 6) + nTickX + nX].cHeight, (float)(nTickY + nY));
                    }
                    if (nX == 63 && nY < 63)
                    {
                        m_vertex[0].diffuse = m_TileMapData[nX + (nY << 6)].dwColor;
                        m_vertex[1].diffuse = m_TileMapData[nX + ((nTickY + nY) << 6)].dwColor;
                        m_vertex[2].diffuse = m_TileMapData[nX + (nY << 6)].dwColor;
                        m_vertex[3].diffuse = m_TileMapData[nX + ((nTickY + nY) << 6)].dwColor;

                        m_vertexVoodoo[0].position = TMVector3((float)nX, (float)m_TileMapData[nX + (nY << 6)].cHeight, (float)nY);
                        m_vertexVoodoo[1].position = TMVector3((float)nX, (float)m_TileMapData[nX + ((nTickY + nY) << 6)].cHeight, (float)(nTickY + nY));
                        m_vertexVoodoo[2].position = TMVector3((float)(nTickX + nX), (float)m_TileMapData[nX + (nY << 6)].cHeight, (float)nY);
                        m_vertexVoodoo[3].position = TMVector3((float)(nTickX + nX), (float)m_TileMapData[nX + ((nTickY + nY) << 6)].cHeight, (float)(nTickY + nY));
                    }
                    if (nY == 63 && nX < 63)
                    {
                        m_vertex[0].diffuse = m_TileMapData[nX + (nY << 6)].dwColor;
                        m_vertex[1].diffuse = m_TileMapData[nX + (nY << 6)].dwColor;
                        m_vertex[2].diffuse = m_TileMapData[(nY << 6) + nTickX + nX].dwColor;
                        m_vertex[3].diffuse = m_TileMapData[(nY << 6) + nTickX + nX].dwColor;

                        m_vertexVoodoo[0].position = TMVector3((float)nX, m_TileMapData[nX + (nY << 6)].cHeight, (float)nY);
                        m_vertexVoodoo[1].position = TMVector3((float)nX, m_TileMapData[nX + (nY << 6)].cHeight, (float)(nTickY + nY));
                        m_vertexVoodoo[2].position = TMVector3((float)(nTickX + nX), m_TileMapData[(nY << 6) + nTickX + nX].cHeight, (float)nY);
                        m_vertexVoodoo[3].position = TMVector3((float)(nTickX + nX), m_TileMapData[(nY << 6) + nTickX + nX].cHeight, (float)(nTickY + nY));
                    }

                    if (m_dwEffStart && m_dwServertime < (m_dwEffStart + 2000))
                    {
                        auto Height = (float)(((4.0f * m_fEffHeight) * (float)(m_dwServertime - m_dwEffStart - 2000)) / 2000.0f);

                        for (int j = 0; j < 4; j++)
                        {
                            auto vecCalc = (float)((float)(m_vecEffset.x - m_vertexVoodoo[j].position.x) * (float)(m_vecEffset.y - m_vertexVoodoo[j].position.z)) / 10.0f;

                            float fCos = cosf(((m_vecEffset.x - m_vertexVoodoo[j].position.x) * (m_vecEffset.y - m_vertexVoodoo[j].position.z))
                                / 10.0f + ((float)m_dwServertime / 300.0f));
                            m_vertexVoodoo[j].position.y = (float)(fCos * Height) + m_vertexVoodoo[j].position.y;
                        }
                    }

                    g_pDevice->SetTexture(0, g_pTextureManager->GetEnvTexture(nTexIndex, 5000));
                    g_pDevice->m_pd3dDevice->SetFVF(322);
                    g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vertexVoodoo, 24);
                    continue;
                }

                int nIndex = m_TileMapData[nX + (nY << 6)].byTileIndex + 10;
                for (int k = 0; k < 4; k++)
                {
                    m_vertex[k].tu1 = TMGround::TileCoordList[(unsigned char)bCoordIndex][k][0];
                    m_vertex[k].tv1 = TMGround::TileCoordList[(unsigned char)bCoordIndex][k][1];

                    if (!m_bDungeon || m_bDungeon == 3 || m_bDungeon == 4)
                    {
                        m_vertex[k].tu2 = TMGround::BackTileCoordList[(unsigned char)bCoordBackIndex][k][0];
                        m_vertex[k].tv2 = TMGround::BackTileCoordList[(unsigned char)bCoordBackIndex][k][1];
                       continue;
                    }

                    if (m_vecOffsetIndex.x < 26 || m_vecOffsetIndex.x > 30 || m_vecOffsetIndex.y < 8 || m_vecOffsetIndex.y > 12)
                    {
                        if (nIndex == 170 || nIndex == 171)
                        {
                            m_vertex[k].tu1 = (float)((float)(m_dwServertime % 10000) / 10000.0f) + m_vertex[k].tu1;

                            if (g_bHideEffect)
                                continue;

                            int nRandV = rand();

                            TMVector3 vecPos = TMVector3((float)((float)((float)nX * 2.0f) + m_vecOffset.x) + 0.5f,
                                (float)((float)m_TileMapData[nX + (nY << 6)].cHeight * 0.1f) + 1.5f,
                                (float)((float)((float)nY * 2.0f) + m_vecOffset.y) + 0.5f);

                            if (nRandV % 200 < 2)
                            {
                                int nRand = rand() % 10;

                                TMEffectBillBoard* mpBill = new TMEffectBillBoard(0, 1000,
                                    (float)((float)nRand * 0.19f) + 0.02f,
                                    (float)((float)nRand * 0.60000002f) + 0.02f,
                                    (float)((float)nRand * 0.19f) + 0.02f,
                                    0.000099999997f, 1, 80);

                                if (mpBill)
                                {
                                    vecPos.x = (float)((float)(rand() % 10 - 5) * 0.02f) + vecPos.x;
                                    vecPos.z = (float)((float)(rand() % 10 - 5) * 0.02f) + vecPos.z;

                                    mpBill->m_vecPosition = vecPos;
                                    mpBill->m_vecStartPos = vecPos;

                                    mpBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                                    mpBill->m_bStickGround = 0;
                                    mpBill->m_nParticleType = 1;
                                    mpBill->m_fParticleV = 0.69999999f;
                                    mpBill->SetColor(0xFFFFAA00);

                                    g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);
                                }
                            }
                            if (m_dwServertime - m_dwLastEffectTime > 2000
                                && !(nX % 2)
                                && !(nY % 3)
                                && (nRandV % 100 < 1))
                            {
                                int glowRand = (rand() % 7);

                                auto pGlow = new TMEffectBillBoard(56, 20000, 0.2f, 0.2f, 0.2f, 0.0f, 1, 80);

                                if (pGlow)
                                {
                                    pGlow->m_vecPosition = TMVector3(
                                        vecPos.x,
                                        (float)(vecPos.y + 1.5f) + (float)((float)glowRand * 0.2f),
                                        vecPos.z);

                                    pGlow->m_vecStartPos = pGlow->m_vecPosition;

                                    pGlow->m_fCircleSpeed = (float)((float)glowRand * 0.1f) + 1.5f;
                                    pGlow->m_fParticleH = (float)((float)glowRand * 0.30000001f) + 3.0f;
                                    pGlow->m_fParticleV = (float)((float)glowRand * 0.050000001f) + 0.2f;
                                    pGlow->m_nParticleType = glowRand % 3 + 6;
                                    pGlow->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                                    pGlow->SetColor(0xFFFFAA00);

                                    g_pCurrentScene->m_pEffectContainer->AddChild(pGlow);
                                }

                                pGlow = new TMEffectBillBoard(60, 20000, 0.07f, 0.07f, 0.07f, 0.0f, 1, 80);

                                if (pGlow)
                                {
                                    pGlow->m_vecPosition = TMVector3(
                                        vecPos.x,
                                        (float)(vecPos.y + 1.5f) + (float)((float)glowRand * 0.2f),
                                        vecPos.z);

                                    pGlow->m_vecStartPos = pGlow->m_vecPosition;

                                    pGlow->m_fCircleSpeed = (float)((float)glowRand * 0.1f) + 1.5f;
                                    pGlow->m_fParticleH = (float)((float)glowRand * 0.30000001f) + 3.0f;
                                    pGlow->m_fParticleV = (float)((float)glowRand * 0.050000001f) + 0.2f;
                                    pGlow->m_nParticleType = glowRand % 3 + 6;
                                    pGlow->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                                    pGlow->SetColor(0xFFFFFF00);

                                    g_pCurrentScene->m_pEffectContainer->AddChild((TreeNode*)pGlow);
                                }

                                if (glowRand < 3)
                                {
                                    auto pFire = new TMSkillFire(vecPos, 1, 0, 0xFFFFFFFF, 0x22331100);

                                    if (pFire)
                                        g_pCurrentScene->m_pEffectContainer->AddChild(pFire);
                                }
                            }
                        }
                        else if (nIndex == 38 || nIndex == 39)
                        {
                            fX[0] = 0.0f;
                            fX[1] = 0.0f;
                            fX[2] = 1.0f;
                            fX[3] = 1.0f;
                            fY[0] = 0.0f;
                            fY[1] = 1.0f;
                            fY[2] = 0.0f;
                            fY[3] = 1.0f;

                            g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, 5);

                            g_pDevice->SetTexture(1, g_pTextureManager->GetEnvTexture(344, 5000));

                            float fAngle = (float)(m_dwServertime % 10000) / 10000.0f;

                            m_vertex[k].tu2 = fX[k];
                            m_vertex[k].tv2 = fY[k] + fAngle;

                            nTexIndex = nIndex + 92;
                        }
                        else if (nIndex >= 62 && nIndex <= 65)
                        {
                            g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, 5);
                            g_pDevice->SetTexture(1, g_pTextureManager->GetEnvTexture(nIndex + 286, 5000));

                            m_vertex[k].tu2 = m_vertex[k].tu1;
                            m_vertex[k].tv2 = m_vertex[k].tv1;

                            nTexIndex = nIndex % 2 + 130;
                        }
                        else
                        {
                            g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, 1);
                        }
                    }
                }

                if (nX < 63 && nY < 63)
                {
                    m_vertex[0].diffuse = m_TileMapData[nX + (nY << 6)].dwColor;
                    m_vertex[1].diffuse = m_TileMapData[nX + ((nTickY + nY) << 6)].dwColor;
                    m_vertex[2].diffuse = m_TileMapData[(nY << 6) + nTickX + nX].dwColor;
                    m_vertex[3].diffuse = m_TileMapData[((nTickY + nY) << 6) + nTickX + nX].dwColor;

                    m_vertex[0].normal = m_TileNormalVector[64 * nY + nX];
                    m_vertex[1].normal = m_TileNormalVector[64 * (nTickY + nY) + nX];
                    m_vertex[2].normal = m_TileNormalVector[64 * nY + nTickX + nX];
                    m_vertex[3].normal = m_TileNormalVector[64 * (nTickY + nY) + nTickX + nX];
                                        
                    m_vertex[0].position = TMVector3((float)nX, (float)m_TileMapData[nX + (nY << 6)].cHeight, (float)nY);
                    m_vertex[1].position = TMVector3((float)nX,
                        (float)m_TileMapData[nX + ((nTickY + nY) << 6)].cHeight,
                        (float)(nTickY + nY));
                    m_vertex[2].position = TMVector3((float)(nTickX + nX),
                        (float)m_TileMapData[(nY << 6) + nTickX + nX].cHeight,
                        (float)nY);
                    m_vertex[3].position = TMVector3((float)(nTickX + nX),
                        (float)m_TileMapData[((nTickY + nY) << 6) + nTickX + nX].cHeight,
                        (float)(nTickY + nY));
                }
                else if (nX == 63 && nY < 63)
                {
                    m_vertex[0].diffuse = m_TileMapData[nX + (nY << 6)].dwColor;
                    m_vertex[1].diffuse = m_TileMapData[nX + ((nTickY + nY) << 6)].dwColor;
                    m_vertex[2].diffuse = m_TileMapData[nX + (nY << 6)].dwColor;
                    m_vertex[3].diffuse = m_TileMapData[nX + ((nTickY + nY) << 6)].dwColor;

                    m_vertex[0].normal = m_TileNormalVector[64 * nY + nX];
                    m_vertex[1].normal = m_TileNormalVector[64 * (nTickY + nY) + nX];
                    m_vertex[2].normal = m_TileNormalVector[64 * nY + nX];
                    m_vertex[3].normal = m_TileNormalVector[64 * (nTickY + nY) + nX];

                    m_vertex[0].position = TMVector3((float)nX, (float)m_TileMapData[nX + (nY << 6)].cHeight, (float)nY);
                    m_vertex[1].position = TMVector3((float)nX,
                        (float)m_TileMapData[nX + ((nTickY + nY) << 6)].cHeight,
                        (float)(nTickY + nY));
                    m_vertex[2].position = TMVector3((float)(nTickX + nX),
                        (float)m_TileMapData[nX + (nY << 6)].cHeight,
                        (float)nY);
                    m_vertex[3].position = TMVector3((float)(nTickX + nX),
                        (float)m_TileMapData[nX + ((nTickY + nY) << 6)].cHeight,
                        (float)(nTickY + nY));
                }
                else if (nY == 63 && nX < 63)
                {
                    m_vertex[0].diffuse = m_TileMapData[nX + (nY << 6)].dwColor;
                    m_vertex[1].diffuse = m_TileMapData[nX + (nY << 6)].dwColor;
                    m_vertex[2].diffuse = m_TileMapData[(nY << 6) + nTickX + nX].dwColor;
                    m_vertex[3].diffuse = m_TileMapData[(nY << 6) + nTickX + nX].dwColor;

                    m_vertex[0].normal = m_TileNormalVector[64 * nY + nX];
                    m_vertex[1].normal = m_TileNormalVector[64 * nY + nX];
                    m_vertex[2].normal = m_TileNormalVector[64 * nY + nTickX + nX];
                    m_vertex[3].normal = m_TileNormalVector[64 * nY + nTickX + nX];

                    m_vertex[0].position = TMVector3((float)nX, (float)m_TileMapData[nX + (nY << 6)].cHeight, (float)nY);
                    m_vertex[1].position = TMVector3((float)nX,
                        (float)m_TileMapData[nX + (nY << 6)].cHeight,
                        (float)(nTickY + nY));
                    m_vertex[2].position = TMVector3((float)(nTickX + nX),
                        (float)m_TileMapData[(nY << 6) + nTickX + nX].cHeight,
                        (float)nY);
                    m_vertex[3].position = TMVector3((float)(nTickX + nX),
                        (float)m_TileMapData[(nY << 6) + nTickX + nX].cHeight,
                        (float)(nTickY + nY));
                }

                if (m_dwEffStart && m_dwServertime < (m_dwEffStart + 2000))
                {
                    float Height = (float)((4.0f * m_fEffHeight) * (float)(m_dwServertime - m_dwEffStart - 2000) / 2000.0f);

                    for (int j = 0; j < 4; j++)
                    {
                        auto vecCalc = (float)((float)(m_vecEffset.x - m_vertex[j].position.x) * (float)(m_vecEffset.y - m_vertex[j].position.z)) / 10.0f;

                        float fCos = cosf(((m_vecEffset.x - m_vertex[j].position.x)
                            * (m_vecEffset.y - m_vertex[j].position.z))
                            / 10.0f + (float)((float)m_dwServertime / 300.0f));

                        m_vertex[j].position.y = (float)(fCos * Height) + m_vertex[j].position.y;
                    }
                }

                g_pDevice->SetTexture(0, g_pTextureManager->GetEnvTexture(nTexIndex, 5000));

                if (!m_bDungeon || m_bDungeon == 3 || m_bDungeon == 4)
                    g_pDevice->SetTexture(1, g_pTextureManager->GetEnvTexture(((unsigned char)m_TileMapData[nX + (nY << 6)].byBackTileIndex + 256), 5000));

                g_pDevice->m_pd3dDevice->SetFVF(594);

                int bVisible = 0;

                for (int m = 0; m < 4; ++m)
                {
                    D3DXVECTOR3 tempVec;
                    tempVec.x = (m_vertex[m].position.x * 2.0f) + m_vecOffset.x;
                    tempVec.y = m_vertex[m].position.y * 0.1f;
                    tempVec.z = (m_vertex[m].position.z * 2.0f) + m_vecOffset.y;

                    D3DXVec3TransformCoord(&vTemp, &tempVec, &g_pDevice->m_matView);
                    D3DXVec3TransformCoord(&vPosTransformed, &vTemp, &g_pDevice->m_matProj);

                    if (vPosTransformed.z >= 0.0f && vPosTransformed.z < 1.0f)
                    {
                        int vPosInX = (int)((((vPosTransformed.x + 1.0f) * (float)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift)) / 2.0f));
                        int vPosInY = (int)((((-vPosTransformed.y + 1.0f) * (float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nWidthShift)) / 2.0f));

                        if ((float)vPosInX > (float)(-50.0f * RenderDevice::m_fWidthRatio)
                            && ((float)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift)
                                + (50.0f * RenderDevice::m_fWidthRatio)) > (float)vPosInX
                            && (float)vPosInY > (float)(-50.0f * RenderDevice::m_fHeightRatio)
                            && ((float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift)
                                + (50.0f * RenderDevice::m_fHeightRatio)) > (float)vPosInY)
                        {
                            bVisible = 1;
                            break;
                        }
                    }
                }
                if (bVisible == 1)
                    g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vertex, 44u);
            }
        }
    }

    if (m_dwServertime - m_dwLastEffectTime > 2000)
        m_dwLastEffectTime = m_dwServertime;

    if (g_pDevice->m_bVoodoo == 1)
        g_pDevice->SetRenderState(D3DRS_LIGHTING, 1);

    g_pDevice->SetRenderState(D3DRS_COLORVERTEX, 0);
    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
    g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1);
    g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, 1);
    g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, 1);

    if (m_bWire == 1)
        g_pDevice->SetRenderState(D3DRS_FILLMODE, 3);

    return 1;
}

int TMGround::FrameMove(unsigned int dwServerTime)
{
    m_dwServertime = g_pTimerManager->GetServerTime();
    TMObject* pFocusedObject = g_pCurrentScene->m_pMyHuman;

    if (pFocusedObject)
    {
        if (g_pCurrentScene->m_pGround == this)
        {
            int nPosX = static_cast<int>((pFocusedObject->m_vecPosition.x - m_vecOffset.x) + 128.0f) / (512 / TextureManager::DYNAMIC_TEXTURE_WIDTH);
            int nPosY = static_cast<int>((pFocusedObject->m_vecPosition.y - m_vecOffset.y) + 256.0f) / (512 / TextureManager::DYNAMIC_TEXTURE_WIDTH);

            auto pUISet = g_pTextureManager->GetUITextureSet(11);
            if (pUISet)
            {
                pUISet->pTextureCoord->nStartX = nPosX - static_cast<int>(((static_cast<float>(TextureManager::DYNAMIC_TEXTURE_WIDTH) / 8.0f) * m_fMiniMapScale));
                pUISet->pTextureCoord->nStartY = static_cast<int>(((static_cast<float>(TextureManager::DYNAMIC_TEXTURE_HEIGHT - nPosY)) - ((static_cast<float>(TextureManager::DYNAMIC_TEXTURE_HEIGHT) / 8.0f) * TMGround::m_fMiniMapScale)));
                pUISet->pTextureCoord->nWidth = static_cast<int>((static_cast<float>(TextureManager::DYNAMIC_TEXTURE_WIDTH) / 4.0f) * m_fMiniMapScale);
                pUISet->pTextureCoord->nHeight = static_cast<int>((static_cast<float>(TextureManager::DYNAMIC_TEXTURE_HEIGHT) / 4.0f) * m_fMiniMapScale);

                pUISet->pTextureCoord->nStartY -= 4;
            }
        }
    }

    return 1;
}

D3DXVECTOR3 TMGround::GetPickPos()
{
    static D3DXVECTOR3 vPickPos(0.0f, -10000.0f, 0.0f);

    D3DXVECTOR3 vPickRayDir;
    D3DXVECTOR3 vPickRayOrig;
    g_pDevice->GetPickRayVector(&vPickRayOrig, &vPickRayDir);
    D3DXVec3Normalize(&vPickRayDir, &vPickRayDir);

    float fU = 0.0f;
    float fV = 0.0f;
    float fDistance = 0.0f;
    TMCamera* pCamera = g_pObjectManager->m_pCamera;
    TMVector2 vecCam{};

    if (pCamera->m_pFocusedObject)
    {
        vecCam = pCamera->m_pFocusedObject->m_vecPosition;
    }
    else
    {
        vecCam.x = g_pObjectManager->m_pCamera->m_cameraPos.x;
        vecCam.y = g_pObjectManager->m_pCamera->m_cameraPos.z;
    }

    int nCamPosX = (int)(vecCam.x - m_vecOffset.x);
    int nCamPosY = (int)(vecCam.y - m_vecOffset.y);
    int nClipIndex = 25;
    int nMinClipIndex = 0;

    if(fabsf(g_pObjectManager->m_pCamera->m_fVerticalAngle) > 1.0f)
        nClipIndex = (int)((pCamera->m_fSightLength * 1.5f) + 8.0f);

    nMinClipIndex = nClipIndex / 2;

    for (int nY = nCamPosY - nClipIndex / 2; nY < nClipIndex + nCamPosY; ++nY)
    {
        if (nY >= 0 && nY <= 127)
        {
            for (int nX = nCamPosX - nClipIndex / 2; nX < nClipIndex + nCamPosX; ++nX)
            {
                if (nX >= 0 && nX <= 127)
                {
                    int nMaskHeight = m_pMaskData[nY][nX];
                    if (nMaskHeight > 127)
                        nMaskHeight = 0;
                    if (nMaskHeight == 127)
                        nMaskHeight = 400;

                    D3DXVECTOR3 vertex[4]{};
                    vertex[0] = D3DXVECTOR3((float)nX + m_vecOffset.x, (float)nMaskHeight * 0.1f, (float)nY + m_vecOffset.y);
                    vertex[1] = D3DXVECTOR3((float)nX + m_vecOffset.x, (float)nMaskHeight * 0.1f, ((float)nY + m_vecOffset.y) + 1.0f);
                    vertex[2] = D3DXVECTOR3(((float)nX + m_vecOffset.x) + 1.0f, (float)nMaskHeight * 0.1f, (float)nY + m_vecOffset.y);
                    vertex[3] = D3DXVECTOR3(((float)nX + m_vecOffset.x) + 1.0f, (float)nMaskHeight * 0.1f, ((float)nY + m_vecOffset.y) + 1.0f);
                    if (D3DXIntersectTri(&vertex[0], &vertex[1], &vertex[2], &vPickRayOrig, &vPickRayDir, &fU, &fV, &fDistance) == 1)
                    {
                        vPickPos.y = vertex[0].y;
                        vPickPos.x = vertex[0].x + fV;
                        vPickPos.z = vertex[0].z + fU;
                        return vPickPos;
                    }
                    if (D3DXIntersectTri(&vertex[3], &vertex[2], &vertex[1], &vPickRayOrig, &vPickRayDir, &fU, &fV, &fDistance) == 1)
                    {
                        vPickPos.y = vertex[3].y;
                        vPickPos.x = vertex[3].x - fV;
                        vPickPos.z = vertex[3].z - fU;
                        return vPickPos;
                    }
                }
            }
        }
    }

    if (pCamera->m_fVerticalAngle <= 0.2f && g_pCurrentScene->m_bAutoRun != 1)
    {
        int vPosInX = 0;
        int vPosInY = 0;
        D3DXVECTOR3 vTemp;
        D3DXVECTOR3 vPosTransformed;

        int nPY = (int)((float)nCamPosY / 2.0f);
        int nMinX = (int)((float)nCamPosX / 2.0f) - 12;
        int nMinY = nPY - 12;
        int nMaxX = (int)((float)nCamPosX / 2.0f) + 12;
        int nMaxY = nPY + 12;

        if (nMinX < 0)
            nMinX = 0;
        if (nMinY < 0)
            nMinY = 0;
        if (nMaxX > 64)
            nMaxX = 63;
        if (nMaxY > 64)
            nMaxY = 63;
        nCamPosX /= 2;
        nCamPosY /= 2;

        for (int j = nMinY; j < nMaxY; ++j)
        {
            if (j >= 0 && j <= 64)
            {
                for (int k = nMinX; k < nMaxX; ++k)
                {
                    if (k >= 0 && k <= 64)
                    {
                        D3DXVECTOR3 vec[4]{};
                        if (k < 64 && j < 64)
                        {
                            vec[0] = D3DXVECTOR3((float)((float)k * 2.0f) + m_vecOffset.x, 
                                (float)m_TileMapData[k + (j << 6)].cHeight * 0.1f,
                                (float)((float)j * 2.0f) + m_vecOffset.y);
                            vec[1] = D3DXVECTOR3((float)((float)k * 2.0f) + m_vecOffset.x,
                                (float)m_TileMapData[k + ((j + 1) << 6)].cHeight * 0.1f,
                                (float)((float)(j + 1) * 2.0f) + m_vecOffset.y);
                            vec[2] = D3DXVECTOR3((float)((float)(k + 1) * 2.0f) + m_vecOffset.x,
                                (float)m_TileMapData[k + (j << 6) + 1].cHeight * 0.1f,
                                (float)((float)j * 2.0f) + m_vecOffset.y);
                            vec[3] = D3DXVECTOR3((float)((float)(k + 1) * 2.0f) + m_vecOffset.x,
                                (float)m_TileMapData[k + ((j + 1) << 6) + 1].cHeight * 0.1f,
                                (float)((float)(j + 1) * 2.0f) + m_vecOffset.y);

                            if (fabsf((((float)m_pMaskData[j][k] * 0.1f) - ((((vec[0].y + vec[1].y) + vec[2].y) + vec[3].y) / 4.0f))) > 1.0f)
                                continue;
                        }

                        if (D3DXIntersectTri(&vec[0], &vec[1], &vec[2], &vPickRayOrig, &vPickRayDir, &fU, &fV, &fDistance) == 1)
                        {
                            int bVisible = 0;
                            for (int i = 0; i < 3; ++i)
                            {
                                D3DXVECTOR3 vecPos;
                                vecPos = vec[i];

                                D3DXVec3TransformCoord(&vTemp, &vecPos, &g_pDevice->m_matView);
                                D3DXVec3TransformCoord(&vPosTransformed, &vTemp, &g_pDevice->m_matProj);
                                if (vPosTransformed.z >= 0.0f && vPosTransformed.z < 1.0f)
                                {
                                    int vPosInX = g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift;
                                    vPosInX = (int)(((vPosTransformed.x + 1.0f) * (float)vPosInX) / 2.0f);
                                    int vPosInY = g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift;
                                    vPosInY = (int)(((-vPosTransformed.y + 1.0f) * (float)vPosInY) / 2.0f);

                                    if ((float)vPosInX > (float)(-100.0f * RenderDevice::m_fWidthRatio)
                                        && (float)((float)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift)
                                            + (float)(100.0f * RenderDevice::m_fWidthRatio)) > (float)vPosInX
                                        && (float)vPosInY > (float)(-100.0f * RenderDevice::m_fHeightRatio)
                                        && (float)((float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift)
                                            + (float)(100.0 * RenderDevice::m_fHeightRatio)) > (float)vPosInY)
                                    {
                                        bVisible = 1;
                                        break;
                                    }
                                }
                            }

                            if (bVisible)
                            {
                                vPickPos.y = vec[0].y;
                                vPickPos.x = (fV * 2.0f) + vec[0].x;
                                vPickPos.z = (fU * 2.0f) + vec[0].z;
                                return vPickPos;
                            }
                        }
                        if (D3DXIntersectTri(&vec[3], &vec[2], &vec[1], &vPickRayOrig, &vPickRayDir, &fU, &fV, &fDistance) == 1)
                        {
                            int bVisible = 0;
                            for (int l = 1; l < 4; ++l)
                            {
                                D3DXVECTOR3 vecPos;
                                vecPos = vec[l];
                                D3DXVec3TransformCoord(&vTemp, &vecPos, &g_pDevice->m_matView);
                                D3DXVec3TransformCoord(&vPosTransformed, &vTemp, &g_pDevice->m_matProj);

                                if (vPosTransformed.z >= 0.0f && vPosTransformed.z < 1.0f)
                                {
                                    int vPosInX = g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift;
                                    vPosInX = (int)(((vPosTransformed.x + 1.0f) * (float)vPosInX) / 2.0f);
                                    int vPosInY = g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift;
                                    vPosInY = (int)(((-vPosTransformed.y + 1.0f) * (float)vPosInY) / 2.0f);


                                    if ((float)vPosInX > (float)(-100.0f * RenderDevice::m_fWidthRatio)
                                        && (float)((float)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift)
                                            + (float)(100.0f * RenderDevice::m_fWidthRatio)) > (float)vPosInX
                                        && (float)vPosInY > (float)(-100.0f * RenderDevice::m_fHeightRatio)
                                        && (float)((float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift)
                                            + (float)(100.0f * RenderDevice::m_fHeightRatio)) > (float)vPosInY)
                                    {
                                        bVisible = 1;
                                        break;
                                    }
                                }
                            }
                            if (bVisible)
                            {
                                vPickPos.y = vec[3].y;
                                vPickPos.x = vec[3].x - (fV * 2.0f);
                                vPickPos.z = vec[3].z - (fU * 2.0f);
                                return vPickPos;
                            }
                        }
                    }
                }
            }
        }

        return D3DXVECTOR3(0.0f, -10000.0f, 0.0f);
    }
    else
    {
        return vPickPos;
    }

    return D3DXVECTOR3();
}

float TMGround::GetHeight(TMVector2 vecPosition)
{
    float fHeight = 1.0f;

    int nX = static_cast<int>((vecPosition.x - m_vecOffset.x) / 2.0f);
    int nY = static_cast<int>((vecPosition.y - m_vecOffset.y) / 2.0f);

    if (nX < 0 || nY < 0 || nX > 64 || nY > 64)
        return -10000.0f;

    D3DXVECTOR3 vPickPos{ 0.0, -10000.0f, 0.0f };
    D3DXVECTOR3 vPickRayDir{ 0.0f, -1.0f, 0.0f };
    D3DXVECTOR3 vPickRayOrig{ vecPosition.x, 100.0f, vecPosition.y };
    D3DXVECTOR3 v0{};
    D3DXVECTOR3 v2{};
    D3DXVECTOR3 v6{};
    D3DXVECTOR3 v8{};

    if (nX < 63 && nY < 63 && nX >= 0 && nY >= 0)
    {
        v0 = D3DXVECTOR3((float)((float)nX * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[nX + (nY << 6)].cHeight * 0.1f,
            (float)((float)nY * 2.0f) + m_vecOffset.y);

        v2 = D3DXVECTOR3((float)((float)(nX + 1) * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[nX + (nY << 6) + 1].cHeight * 0.1f,
            (float)((float)nY * 2.0f) + m_vecOffset.y);

        v6 = D3DXVECTOR3((float)((float)nX * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[nX + ((nY + 1) << 6)].cHeight * 0.1f,
            (float)((float)(nY + 1) * 2.0f) + m_vecOffset.y);

        v8 = D3DXVECTOR3((float)((float)(nX + 1) * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[nX + ((nY + 1) << 6) + 1].cHeight * 0.1f,
            (float)((float)(nY + 1) * 2.0f) + m_vecOffset.y);
    }
    if (nX == 63)
    {
        v0 = D3DXVECTOR3((float)((float)63 * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[(nY << 6) + 63].cHeight * 0.1f,
            (float)((float)nY * 2.0f) + m_vecOffset.y);

        v2 = D3DXVECTOR3((float)((float)64 * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[(nY << 6) + 63].cHeight * 0.1f,
            (float)((float)nY * 2.0f) + m_vecOffset.y);

        v6 = D3DXVECTOR3((float)((float)63 * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[((nY + 1) << 6) + 63].cHeight * 0.1f,
            (float)((float)(nY + 1) * 2.0f) + m_vecOffset.y);

        v8 = D3DXVECTOR3((float)((float)64 * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[((nY + 1) << 6) + 63].cHeight * 0.1f,
            (float)((float)(nY + 1) * 2.0f) + m_vecOffset.y);
    }
    else if (nY == 63)
    {
        v0 = D3DXVECTOR3((float)((float)nX * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[nX + 4032].cHeight * 0.1f,
            (float)((float)63 * 2.0f) + m_vecOffset.y);

        v2 = D3DXVECTOR3((float)((float)(nX + 1) * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[nX + 4033].cHeight * 0.1f,
            (float)((float)63 * 2.0f) + m_vecOffset.y);

        v6 = D3DXVECTOR3((float)((float)nX * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[nX + 4032].cHeight * 0.1f,
            (float)((float)64 * 2.0f) + m_vecOffset.y);

        v8 = D3DXVECTOR3((float)((float)(nX + 1) * 2.0f) + m_vecOffset.x,
            (float)m_TileMapData[nX + 4033].cHeight * 0.1f,
            (float)((float)64 * 2.0f) + m_vecOffset.y);
    }
   
    float fU = 0.0;
    float fV = 0.0;
    float fDis = 0.0f;

    if (D3DXIntersectTri(&v0, &v2, &v6, &vPickRayOrig, &vPickRayDir, &fU, &fV, &fDis) == 1)
        return (100.0f - fDis);
    
    if (D3DXIntersectTri(&v8, &v6, &v2, &vPickRayOrig, &vPickRayDir, &fU, &fV, &fDis) == 1)
        return (100.0f - fDis);

    if (nX < 0 || nY < 0 || nX > 63 || nY > 63)
        return -10000.0f;

    if (nX >= 0 && nX < 63 && nY >= 0 && nY < 63)
    {
        fHeight += m_TileMapData[nX + (nY << 6)].cHeight;
        fHeight += m_TileMapData[nX + (nY << 6) + 1].cHeight;
        fHeight += m_TileMapData[nX + ((nY + 1) << 6)].cHeight;
        fHeight += m_TileMapData[nX + ((nY + 1) << 6) + 1].cHeight;
    }
    else if (nX == 63)
    {
        fHeight += m_TileMapData[(nY << 6) + 63].cHeight;
        fHeight += m_TileMapData[(nY << 6) + 63].cHeight;
        fHeight += m_TileMapData[((nY + 1) << 6) + 63].cHeight;
        fHeight += m_TileMapData[((nY + 1) << 6) + 63].cHeight;
    }
    else if (nY == 63)
    {
        fHeight += m_TileMapData[nX + 4032].cHeight;
        fHeight += m_TileMapData[nX + 4033].cHeight;
        fHeight += m_TileMapData[nX + 4032].cHeight;
        fHeight += m_TileMapData[nX + 4033].cHeight;
    }
	
    return (fHeight * 0.1f) / 4.0f;
}

int TMGround::GetMask(TMVector2 vecPosition)
{
    int nMaskX = (int)(vecPosition.x - m_vecOffset.x);
    int nMaskY = (int)(vecPosition.y - m_vecOffset.y);

    if (nMaskX >= 0 && nMaskY >= 0 && nMaskX < 128 && nMaskY < 128)
        return m_pMaskData[nMaskY][nMaskX];

    return -10000;
}

D3DCOLORVALUE TMGround::GetColor(TMVector2 vecPosition)
{
    int nX = static_cast<int>((vecPosition.x - m_vecOffset.x) / 2);
    int nY = static_cast<int>((vecPosition.y - m_vecOffset.y) / 2);

    int dwColor[4]{ 0 };
    if (nX >= 0 && nX < 63 && nY >= 0 && nY < 63)
    {
        dwColor[0] = m_TileMapData[nX + (nY << 6)].dwColor;
        dwColor[1] = m_TileMapData[nX + (nY << 6) + 1].dwColor;
        dwColor[2] = m_TileMapData[nX + ((nY + 1) << 6)].dwColor;
        dwColor[3] = m_TileMapData[nX + ((nY + 1) << 6) + 1].dwColor;
    }
    else if (nX == 63)
    {
        dwColor[0] = m_TileMapData[(nY << 6) + 63].dwColor;
        dwColor[1] = m_TileMapData[(nY << 6) + 63].dwColor;
        dwColor[2] = m_TileMapData[((nY + 1) << 6) + 63].dwColor;
        dwColor[3] = m_TileMapData[((nY + 1) << 6) + 63].dwColor;
    }
    else if (nX == 63)
    {
        dwColor[0] = m_TileMapData[nX + 4032].dwColor;
        dwColor[1] = m_TileMapData[nX + 4033].dwColor;
        dwColor[2] = m_TileMapData[nX + 4032].dwColor;
        dwColor[3] = m_TileMapData[nX + 4033].dwColor;
    }

    D3DCOLORVALUE color[4]{};
    for (int i = 0; i < 4; ++i)
    {
        color[i].r = ((0xFF0000 & dwColor[i]) >> 16) / 256.0f;
        color[i].g = ((dwColor[i] & 0xFF00) >> 8) / 256.0f;
        color[i].b = (dwColor[i] & 0xFF) / 256.0f;
    }

    float fDX = ((float)nX * 2.0f) - (vecPosition.x - m_vecOffset.x);
    float fDY = ((float)nY * 2.0f) - (vecPosition.y - m_vecOffset.y);

    D3DCOLORVALUE result{};

    result.g = (((((fDX + fDY) * color[3].g) + (((4.0f - fDX) - fDY) * color[0].g)) + (((fDX + 2.0f) - fDY) * color[1].g)) + (((2.0f - fDX) + fDY) * color[2].g)) / 12.0f;
    result.b = (((((fDX + fDY) * color[3].b) + (((4.0f - fDX) - fDY) * color[0].b)) + (((fDX + 2.0f) - fDY) * color[1].b)) + (((2.0f - fDX) + fDY) * color[2].b)) / 12.0f;
    result.r = (((((fDX + fDY) * color[3].r) + (((4.0f - fDX) - fDY) * color[0].r)) + (((fDX + 2.0f) - fDY) * color[1].r)) + (((2.0f - fDX) + fDY) * color[2].r)) / 12.0f;
    result.a = 1.0f;

	return result;
}

int TMGround::GetTileType(TMVector2 vecPosition)
{
    int nX = static_cast<int>(vecPosition.x - m_vecOffset.x);
    int nY = static_cast<int>(vecPosition.y - m_vecOffset.y);

    if (m_pVAttrData[nY][nX] == 1)
        return 1;

    int nIndex = m_TileMapData[nX / 2 + (nY / 2 << 6)].byTileIndex + 10;

    if (nIndex >= 14 && nIndex <= 17 && nIndex >= 38 && nIndex <= 77 && nIndex >= 86 && nIndex <= 101 && nIndex >= 130 && nIndex <= 149)
        return 0;

    if (nIndex >= 186 && nIndex <= 193)
        return 11;

    if (nIndex >= 202 && nIndex <= 205)
        return 8;

    if (nIndex < 230 || nIndex > 231)
        return 3;

    return 9;
}

void TMGround::SetColor(TMVector2 vecPosition, unsigned int dwColor)
{
    int nX = static_cast<int>(vecPosition.x - m_vecOffset.x) / 2;
    int nY = static_cast<int>(vecPosition.y - m_vecOffset.y) / 2;

    if (nX >= 0 && nX <= 63 && nY >= 0 && nY <= 63)
        m_TileMapData[nX + (nY << 6)].dwColor = dwColor;
}

TMVector3 TMGround::GetNormalInGround(int nX, int nY)
{
    TMVector3 vRetNormal(0.0f, 1.0f, 0.0f);
    TMVector3 vNormal[4]{};
    TMVector3 vAround[4]{};

    float fCurHeight = (float)m_TileMapData[nX + (nY << 6)].cHeight;

    if (nX > 0 && nX < 64 && nY > 0 && nY < 64)
    {
        vAround[0] = TMVector3(-1.0f, (float)m_TileMapData[nX + (nY << 6) - 1].cHeight, 0.0f);
        vAround[1] = TMVector3(0.0f, (float)m_TileMapData[nX + ((nY + 1) << 6)].cHeight, 1.0f);
        vAround[2] = TMVector3(1.0f, (float)m_TileMapData[nX + (nY << 6) + 1].cHeight, 0.0f);
        vAround[3] = TMVector3(0.0f, (float)m_TileMapData[nX + ((nY - 1) << 6)].cHeight, -1.0f);

        vNormal[0] = ComputeNormalVector(TMVector3(0.0f, fCurHeight, 0.0f), vAround[0], vAround[1]);
        vNormal[1] = ComputeNormalVector(TMVector3(0.0f, fCurHeight, 0.0f), vAround[1], vAround[2]);
        vNormal[2] = ComputeNormalVector(TMVector3(0.0f, fCurHeight, 0.0f), vAround[2], vAround[3]);
        vNormal[3] = ComputeNormalVector(TMVector3(0.0f, fCurHeight, 0.0f), vAround[3], vAround[0]);

        vRetNormal = (vNormal[0] + vNormal[1] + vNormal[2] + vNormal[3]) / 4.0f;
    }

    return vRetNormal;
}

int TMGround::SetMiniMapData()
{
    for (int nY = 0; nY < 3; ++nY)
    {
        for (int nX = 0; nX < 3; ++nX)
        {
            char szMapName[32] = { 0 };

            sprintf_s(szMapName, "UI\\m%02d%02d.wyt",
                m_vecOffsetIndex.x + nX - 1,
                m_vecOffsetIndex.y + nY - 1);

            int nSrcIndex = g_pTextureManager->GetUITextureIndex(szMapName);
            if (nSrcIndex < 0)
                nSrcIndex = 13;

            g_pTextureManager->GenerateTexture(4, nSrcIndex, nX << 7, (2 - nY) << 7, 0, 0, 128, 128);
        }
    }

    return 1;
}

void TMGround::SetAttatchEnable(int nX, int nY)
{
    if (nX == 1 && nY == 1)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 16 && nY == 15)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 16 && nY == 16)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 17 && nY == 16)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 18 && nY == 16)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 18 && nY == 17)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 19 && nY == 16)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 19 && nY == 15)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 1;
    }
    else if (nX == 20 && nY == 16)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 20 && nY == 15)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 19 && nY == 14)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 1;
    }
    else if (nX == 19 && nY == 13)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 1;
    }
    else if (nX == 19 && nY == 12)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 20 && nY == 13)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 18 && nY == 13)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 18 && nY == 12)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 17 && nY == 13)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 17 && nY == 12)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 1;
    }
    else if (nX == 17 && nY == 11)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 1;
    }
    else if (nX == 17 && nY == 10)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 1;
    }
    else if (nX == 17 && nY == 9)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 15 && nY == 13)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 16 && nY == 12)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 15 && nY == 12)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 14 && nY == 13)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 6 && nY == 28)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 13 && nY == 31)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 14 && nY == 30)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 15 && nY == 31)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 13 && nY == 13)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 1;
    }
    else if (nX == 12 && nY == 13)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 11 && nY == 13)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 10 && nY == 13)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 9 && nY == 13)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 8 && nY == 13)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 10 && nY == 14)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 13 && nY == 14)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 13 && nY == 12)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 1 && nY == 31)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 1 && nY == 29)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 2 && nY == 29)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 3 && nY == 29)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 4 && nY == 29)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 5 && nY == 29)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 3 && nY == 30)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 1;
    }
    else if (nX == 3 && nY == 31)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 5 && nY == 31)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 6 && nY == 31)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 7 && nY == 31)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 6 && nY == 30)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 7 && nY == 29)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 8 && nY == 29)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 10 && nY == 11)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 9 && nY == 31)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 10 && nY == 31)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 11 && nY == 31)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 10 && nY == 29)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 11 && nY == 29)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 9 && nY == 28)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 8 && nY == 27)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 10 && nY == 27)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 8 && nY == 2)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 9 && nY == 1)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 10 && nY == 2)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 13 && nY == 28)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 14 && nY == 28)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 17 && nY == 31)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 18 && nY == 31)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 19 && nY == 31)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 17 && nY == 30)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 18 && nY == 30)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX == 19 && nY == 30)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 17 && nY == 28)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 31 && nY == 31)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 25 && nY == 13)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 26 && nY == 8)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 26 && nY == 9)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 26 && nY == 10)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 26 && nY == 11)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 26 && nY == 12)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX == 27 && nY == 11)
    {
        m_cLeftEnable = 2;
        m_cRightEnable = 2;
        m_cUpEnable = 2;
        m_cDownEnable = 2;
    }
    else if (nX < 26)
    {
        if (nX == 8 && nY == 16)
        {
            m_cLeftEnable = 0;
            m_cRightEnable = 1;
            m_cUpEnable = 1;
            m_cDownEnable = 0;
        }
        else if (nX == 9 && nY == 16)
        {
            m_cLeftEnable = 1;
            m_cRightEnable = 0;
            m_cUpEnable = 1;
            m_cDownEnable = 0;
        }
        else if (nX == 8 && nY == 15)
        {
            m_cLeftEnable = 0;
            m_cRightEnable = 1;
            m_cUpEnable = 0;
            m_cDownEnable = 1;
        }
        else if (nX == 9 && nY == 15)
        {
            m_cLeftEnable = 1;
            m_cRightEnable = 0;
            m_cUpEnable = 0;
            m_cDownEnable = 1;
        }
    }
    else if (nX == 28 && nY == 24)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 28 && nY == 23)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 1;
    }
    else if (nX == 27 && nY == 23)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 0;
    }
    else if (nX == 29 && nY == 23)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 2;
        m_cUpEnable = 1;
        m_cDownEnable = 2;
    }
    else if (nX == 27 && nY == 22)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 28 && nY == 22)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 1;
        m_cDownEnable = 1;
    }
    else if (nX == 28 && nY == 21)
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 29 && nY == 22)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 1;
        m_cUpEnable = 0;
        m_cDownEnable = 1;
    }
    else if (nX == 30 && nY == 22)
    {
        m_cLeftEnable = 1;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
    else if (nX != 29 || nY != 27)
    {
        if (nX == 28 && nY == 28)
        {
            m_cLeftEnable = 0;
            m_cRightEnable = 0;
            m_cUpEnable = 0;
            m_cDownEnable = 0;
        }
        else if (nX == 30 && nY == 28)
        {
            m_cLeftEnable = 0;
            m_cRightEnable = 0;
            m_cUpEnable = 0;
            m_cDownEnable = 0;
        }
    }
    else
    {
        m_cLeftEnable = 0;
        m_cRightEnable = 0;
        m_cUpEnable = 0;
        m_cDownEnable = 0;
    }
}

int TMGround::IsInWater(TMVector2 vecPosition, float fHeight, float* pfWaterHeight)
{
    int i = 0;
    for (i = 0; ; ++i)
    {
        if (i >= 10)
            return 0;

        if (m_pSeaList[i])
        {
            POINT ptPos{};
            ptPos.x = static_cast<LONG>(vecPosition.x);
            ptPos.y = static_cast<LONG>(vecPosition.y);

            if (PtInRect(&m_pSeaList[i]->m_rectRange, ptPos) == 1)
                break;
        }
    }

    if (m_pSeaList[i]->m_fHeight <= fHeight)
        return 0;

    *pfWaterHeight = m_pSeaList[i]->m_fHeight;
	return 1;
}

float TMGround::GetWaterHeight(TMVector2 vecPosition, float* pfWaterHeight)
{
    for (int i = 0; i < 10; ++i)
    {
        if (m_pSeaList[i])
        {
            float fHeight = m_pSeaList[i]->GetHeight(vecPosition.x, vecPosition.y);

            if (fHeight > -100.0f)
            {
                *pfWaterHeight = fHeight + m_pSeaList[i]->m_fHeight;

                return *pfWaterHeight;
            }
        }
    }

    return -100.0f;
}
