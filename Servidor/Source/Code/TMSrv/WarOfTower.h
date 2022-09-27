#pragma once

#include <stdio.h>
#include "..\Basedef.h"


class WarOfTower
{

public:

	static void Clear();

	static void Initialize();

	static void StandByProcess();

	static void Tower(int a_iConn, int a_iTower);

	static void CreateTower(int a_iTower, int a_iMob);

	static void KilledTower(int a_iConn, int a_iTarget, int a_iPosX, int a_iPosY);

	static bool AttackTower(int a_iConn, int a_iTarget);

};