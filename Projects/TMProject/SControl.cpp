#include "pch.h"
#include "EventTranslator.h"
#include "SGrid.h"
#include "SControl.h"

unsigned int SControl::m_dwStaticID{ 0 };
int SControl::m_nGridCellSize{ 35 };
int SCursor::m_nCursorType{ 0 };
HCURSOR SCursor::m_hCursor1{};
HCURSOR SCursor::m_hCursor2{};