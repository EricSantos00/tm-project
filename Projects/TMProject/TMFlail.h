#pragma once

#include "TMObject.h"
#include "Structures.h"

class TMEffectBillBoard;
class TMFlail : public TMObject
{
public:
	TMFlail();
	~TMFlail();

	int FrameMove(unsigned int dwServerTime) override;
	int Render() override;

public:
	short m_sState;
	TMVector3 m_vecHeadPos;
	TMVector3 m_vecTailPos;
	TMEffectBillBoard* m_pHeadEffect;
};