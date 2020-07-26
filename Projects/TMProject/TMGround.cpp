#include "pch.h"
#include "TMSea.h"
#include "TMScene.h"
#include "TMGlobal.h"
#include "TMHuman.h"
#include "TMLog.h"
#include "TMGround.h"

float TMGround::TileCoordList[8][4][2] =
{
  { {  0.0,  0.0 }, {  0.0,  1.0 }, {  1.0,  0.0 }, {  1.0,  1.0 } },
  { {  1.0,  0.0 }, {  0.0,  0.0 }, {  1.0,  1.0 }, {  0.0,  1.0 } },
  { {  1.0,  1.0 }, {  1.0,  0.0 }, {  0.0,  1.0 }, {  0.0,  0.0 } },
  { {  0.0,  1.0 }, {  1.0,  1.0 }, {  0.0,  0.0 }, {  1.0,  0.0 } },
  { {  0.0,  0.0 }, {  1.0,  0.0 }, {  0.0,  1.0 }, {  1.0,  1.0 } },
  { {  0.0,  1.0 }, {  0.0,  0.0 }, {  1.0,  1.0 }, {  1.0,  0.0 } },
  { {  1.0,  1.0 }, {  0.0,  1.0 }, {  1.0,  0.0 }, {  0.0,  0.0 } },
  { {  1.0,  0.0 }, {  1.0,  1.0 }, {  0.0,  0.0 }, {  0.0,  1.0 } }
};

float TMGround::BackTileCoordList[32][4][2] =
{
  { {  0.0,  0.0 }, {  0.0,  0.5 }, {  0.5,  0.0 }, {  0.5,  0.5 } },
  { {  1.0,  0.0 }, {  0.5,  0.0 }, {  1.0,  0.5 }, {  0.5,  0.5 } },
  { {  1.0,  1.0 }, {  1.0,  0.5 }, {  0.5,  1.0 }, {  0.5,  0.5 } },
  { {  0.0,  1.0 }, {  0.5,  1.0 }, {  0.0,  0.5 }, {  0.5,  0.5 } },
  { {  0.0,  0.0 }, {  0.5,  0.0 }, {  0.0,  0.5 }, {  0.5,  0.5 } },
  { {  0.0,  1.0 }, {  0.0,  0.5 }, {  0.5,  1.0 }, {  0.5,  0.5 } },
  { {  1.0,  1.0 }, {  0.5,  1.0 }, {  1.0,  0.5 }, {  0.5,  0.5 } },
  { {  1.0,  0.0 }, {  1.0,  0.5 }, {  0.5,  0.0 }, {  0.5,  0.5 } },
  { {  0.0,  0.5 }, {  0.0,  1.0 }, {  0.5,  0.5 }, {  0.5,  1.0 } },
  { {  0.5,  0.0 }, {  0.0,  0.0 }, {  0.5,  0.5 }, {  0.0,  0.5 } },
  { {  1.0,  0.5 }, {  1.0,  0.0 }, {  0.5,  0.5 }, {  0.5,  0.0 } },
  { {  0.5,  1.0 }, {  1.0,  1.0 }, {  0.5,  0.5 }, {  1.0,  0.5 } },
  { {  0.5,  0.0 }, {  1.0,  0.0 }, {  0.5,  0.5 }, {  1.0,  0.5 } },
  { {  0.0,  0.5 }, {  0.0,  0.0 }, {  0.5,  0.5 }, {  0.5,  0.0 } },
  { {  0.5,  1.0 }, {  0.0,  1.0 }, {  0.5,  0.5 }, {  0.0,  0.5 } },
  { {  1.0,  0.5 }, {  1.0,  1.0 }, {  0.5,  0.5 }, {  0.5,  1.0 } },
  { {  0.5,  0.0 }, {  0.5,  0.5 }, {  1.0,  0.0 }, {  1.0,  0.5 } },
  { {  1.0,  0.5 }, {  0.5,  0.5 }, {  1.0,  1.0 }, {  0.5,  1.0 } },
  { {  0.5,  1.0 }, {  0.5,  0.5 }, {  0.0,  1.0 }, {  0.0,  0.5 } },
  { {  0.0,  0.5 }, {  0.5,  0.5 }, {  0.0,  0.0 }, {  0.5,  0.0 } },
  { {  0.0,  0.5 }, {  0.5,  0.5 }, {  0.0,  1.0 }, {  0.5,  1.0 } },
  { {  0.5,  1.0 }, {  0.5,  0.5 }, {  1.0,  1.0 }, {  1.0,  0.5 } },
  { {  1.0,  0.5 }, {  0.5,  0.5 }, {  1.0,  0.0 }, {  0.5,  0.0 } },
  { {  0.5,  0.0 }, {  0.5,  0.5 }, {  0.0,  0.0 }, {  0.0,  0.5 } },
  { {  0.5,  0.5 }, {  0.5,  1.0 }, {  1.0,  0.5 }, {  1.0,  1.0 } },
  { {  0.5,  0.5 }, {  0.0,  0.5 }, {  0.5,  1.0 }, {  0.0,  1.0 } },
  { {  0.5,  0.5 }, {  0.5,  0.0 }, {  0.0,  0.5 }, {  0.0,  0.0 } },
  { {  0.5,  0.5 }, {  1.0,  0.5 }, {  0.5,  0.0 }, {  1.0,  0.0 } },
  { {  0.5,  0.5 }, {  1.0,  0.5 }, {  0.5,  1.0 }, {  1.0,  1.0 } },
  { {  0.5,  0.5 }, {  0.5,  0.0 }, {  1.0,  0.5 }, {  1.0,  0.0 } },
  { {  0.5,  0.5 }, {  0.0,  0.5 }, {  0.5,  0.0 }, {  0.0,  0.0 } },
  { {  0.5,  0.5 }, {  0.5,  1.0 }, {  0.0,  0.5 }, {  0.0,  1.0 } }
};

int TMGround::m_nCheckSum[64][32] =
{
  {
    4294967295,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
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
        m_vertex[i].diffuse = 0x0FFFFFF;
        m_vertexVoodoo[i].diffuse = 0x0FFFFFF;
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
    }

    if (m_bFirst != 1)
    {
        SetPos(0, 0);
        return;
    }

    LOG_WRITELOG("DataFile NotFound");

    if (!g_pCurrentScene->m_bCriticalError)
        g_pCurrentScene->LogMsgCriticalError(4, 0, 0, 0, 0);

    g_pCurrentScene->m_bCriticalError = 1;
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

    m_vecOffset.x = m_vecOffsetIndex.x * 2.0f * 64.0f;
    m_vecOffset.y = m_vecOffsetIndex.y * 2.0f * 64.0f;

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

    bool result = false;
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
            pGround->m_TileMapData[i * 64].cHeight = m_TileMapData[(i << 6) + 63].cHeight;
            pGround->m_TileMapData[i * 64].dwColor = m_TileMapData[(i << 6) + 63].dwColor;

            pGround->m_TileNormalVector[64 * i] = m_TileNormalVector[64 * i + 63];
        }

        m_nMiniMapPos = 0;
        m_pRightGround->m_nMiniMapPos = 1;
        result = true;
    }
    else if (pGround->m_vecOffsetIndex.x == m_vecOffsetIndex.x - 1)
    {
        m_pLeftGround = pGround;
        m_pLeftGround->m_pRightGround = this;

        for (int i = 0; i < 64; ++i)
        {
            pGround->m_TileMapData[i * 64].cHeight = m_TileMapData[(i << 6) + 63].cHeight;
            pGround->m_TileMapData[i * 64].dwColor = m_TileMapData[(i << 6) + 63].dwColor;

            pGround->m_TileNormalVector[64 * i] = m_TileNormalVector[64 * i + 63];
        }

        m_nMiniMapPos = 1;
        m_pLeftGround->m_nMiniMapPos = 0;
        result = true;
    }
    else if (pGround->m_vecOffsetIndex.y == m_vecOffsetIndex.y + 1)
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
        result = true;
    }
    else if (pGround->m_vecOffsetIndex.y == m_vecOffsetIndex.y - 1)
    {
        m_pUpGround = pGround;
        m_pUpGround->m_pDownGround = this;

        for (int i = 0; i < 64; ++i)
        {
            pGround->m_TileMapData[i].cHeight = m_TileMapData[i + 4032].cHeight;
            pGround->m_TileMapData[i].dwColor = m_TileMapData[i + 4032].dwColor;

            pGround->m_TileNormalVector[i] = m_TileNormalVector[i + 4032];
        }

        m_nMiniMapPos = 2;
        m_pUpGround->m_nMiniMapPos = 0;
        result = true;
    }

    return result;
}

int TMGround::LoadTileMap(char* szFileName)
{
	return 0;
}

int TMGround::Render()
{
	return 0;
}

int TMGround::FrameMove(unsigned int dwServerTime)
{
    m_dwServertime = g_pTimerManager->GetServerTime();
    TMObject* pFocusedObject = g_pCurrentScene->m_pMyHuman;

    if (pFocusedObject)
    {
        if (g_pCurrentScene->m_pGround == this)
        {
            int nPosX = static_cast<int>(pFocusedObject->m_vecPosition.x - m_vecOffset.x + 128.0f) / 512 / TextureManager::DYNAMIC_TEXTURE_WIDTH;
            int nPosY = static_cast<int>(pFocusedObject->m_vecPosition.y - m_vecOffset.y + 256.0f) / 512 / TextureManager::DYNAMIC_TEXTURE_WIDTH;

            auto pUISet = g_pTextureManager->GetUITextureSet(11);
            if (pUISet)
            {
                pUISet->pTextureCoord->nStartX = nPosX - ((static_cast<float>(TextureManager::DYNAMIC_TEXTURE_WIDTH) / 8.0f) * m_fMiniMapScale);
                pUISet->pTextureCoord->nStartY = nPosY - ((static_cast<float>(TextureManager::DYNAMIC_TEXTURE_HEIGHT) / 8.0f) * m_fMiniMapScale);
                pUISet->pTextureCoord->nWidth = (static_cast<float>(TextureManager::DYNAMIC_TEXTURE_WIDTH) / 4.0f) * m_fMiniMapScale;
                pUISet->pTextureCoord->nHeight = (static_cast<float>(TextureManager::DYNAMIC_TEXTURE_HEIGHT) / 4.0f) * m_fMiniMapScale;

                pUISet->pTextureCoord->nStartY -= 4;
            }
        }
    }

    return 1;
}

D3DXVECTOR3* TMGround::GetPickPos(D3DXVECTOR3* result)
{
	return nullptr;
}

float TMGround::GetHeight(TMVector2 vecPosition)
{
	return 0.0f;
}

int TMGround::GetMask(TMVector2 vecPosition)
{
	return 0;
}

D3DCOLORVALUE* TMGround::GetColor(D3DCOLORVALUE* result, TMVector2 vecPosition)
{
	return nullptr;
}

int TMGround::GetTileType(TMVector2 vecPosition)
{
	return 0;
}

void TMGround::SetColor(TMVector2 vecPosition, unsigned int dwColor)
{
}

TMVector3* TMGround::GetNormalInGround(TMVector3* result, int nX, int nY)
{
	return nullptr;
}

int TMGround::SetMiniMapData()
{
	return 0;
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
	return 0;
}

float TMGround::GetWaterHeight(TMVector2 vecPosition, float* pfWaterHeight)
{
	return 0.0f;
}
