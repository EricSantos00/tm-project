#include "pch.h"
#include "TMFieldScene.h"

RECT TMFieldScene::m_rectWarning[7] =
{
  { 2255, 1535, 2263, 1538 },
  { 150, 3788, 156, 3793 },
  { 150, 3711, 156, 3772 },
  { 154, 3773, 157, 3780 },
  { 1075, 1708, 1078, 1713 },
  { 1171, 4076, 1177, 4079 },
  { 2362, 4041, 2369, 4044 }
};

int TMFieldScene::m_bPK = 0;
unsigned short TMFieldScene::m_usProgress = 0;
unsigned int TMFieldScene::m_dwCargoID = 0;

TMFieldScene::TMFieldScene()
{
}

TMFieldScene::~TMFieldScene()
{
}

int TMFieldScene::InitializeScene()
{
	return 0;
}

int TMFieldScene::OnControlEvent(unsigned int idwControlID, unsigned int idwEvent)
{
	return 0;
}

int TMFieldScene::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

int TMFieldScene::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

int TMFieldScene::OnPacketEvent(unsigned int dwCode, char* buf)
{
	return 0;
}

int TMFieldScene::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::OnAccel(int nMsg)
{
	return 0;
}

void TMFieldScene::PGTVisible(unsigned int dwServerTime)
{
}

void TMFieldScene::MouseMove(int nX, int nY)
{
}

int TMFieldScene::SkillUse(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime, int bMoving, TMHuman* pTarget)
{
	return 0;
}

int TMFieldScene::AutoSkillUse(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime, int bMoving, TMHuman* pTarget)
{
	return 0;
}

int TMFieldScene::MouseClick_NPC(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::CheckMerchant(TMHuman* pOver)
{
	return 0;
}

int TMFieldScene::MouseLButtonDown(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::MobAttack(unsigned int wParam, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::MobMove(D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::MobMove2(TMVector2 vec, unsigned int dwServerTime)
{
	return 0;
}

void TMFieldScene::DropItem(unsigned int dwServerTime)
{
}

int TMFieldScene::TimeDelay(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::GetItem(TMItem* pItem)
{
	return 0;
}

void TMFieldScene::FrameMove_KhepraDieEffect(unsigned int dwServerTime)
{
}

void TMFieldScene::SetVisibleInventory()
{
}

void TMFieldScene::SetVisibleCharInfo()
{
}

void TMFieldScene::SetVisibleShop(int bShow)
{
}

void TMFieldScene::SetVisibleCargo(int bShow)
{
}

void TMFieldScene::SetVisibleCargo1(int bShow)
{
}

void TMFieldScene::SetVisibleTrade(int bShow)
{
}

void TMFieldScene::ClearCombine()
{
}

void TMFieldScene::ClearCombine4()
{
}

void TMFieldScene::DoCombine()
{
}

void TMFieldScene::DoCombine4()
{
}

void TMFieldScene::SetVisibleMixItem(int bShow)
{
}

void TMFieldScene::SetVisibleMixItemTiini(int bShow)
{
}

void TMFieldScene::SetVisibleHellGateStore(int bShow)
{
}

void TMFieldScene::SetVisibleGamble(int bShow, char cType)
{
}

void TMFieldScene::SetVisiblePotal(int bShow, int nPos)
{
}

void TMFieldScene::SetVisibleMiniMap()
{
}

void TMFieldScene::SetVisibleParty()
{
}

void TMFieldScene::SetVisibleSkillMaster()
{
}

void TMFieldScene::SetVisibleSkill()
{
}

void TMFieldScene::SetVisibleServerWar()
{
}

void TMFieldScene::SetVisibleRefuseServerWar()
{
}

void TMFieldScene::SetInVisibleInputCoin()
{
}

void TMFieldScene::SetGridState()
{
}

void TMFieldScene::SetEquipGridState(int bDefault)
{
}

void TMFieldScene::UpdateScoreUI(unsigned int unFlag)
{
}

void TMFieldScene::UpdateSkillBelt()
{
}

void TMFieldScene::UpdateMyHuman()
{
}

void TMFieldScene::SetMyHumanExp(long long unExp, int nFakeExp)
{
}

void TMFieldScene::IncSkillSel()
{
}

void TMFieldScene::SetShortSkill(int nIndex, SGridControlItem* pGridItem)
{
}

void TMFieldScene::SetSkillColor(TMHuman* pAttacker, char cSkillIndex)
{
}

void TMFieldScene::OnESC()
{
}

void TMFieldScene::FindAuto()
{
}

int TMFieldScene::FindProcess(unsigned int processID)
{
	return 0;
}

void TMFieldScene::SetAutoOption(int nIndex, char* szString)
{
}

void TMFieldScene::SetAutoSkillNum(int nCount)
{
}

void TMFieldScene::SetCameraView()
{
}

void TMFieldScene::InitCameraView()
{
}

void TMFieldScene::SetPK()
{
}

void TMFieldScene::SetVisibleNameLabel()
{
}

void TMFieldScene::SetAutoTarget()
{
}

void TMFieldScene::SetVisibleAutoTrade(int bShow, int bCargo)
{
}

void TMFieldScene::SetWhisper(char cOn)
{
}

void TMFieldScene::SetPartyChat(char cOn)
{
}

void TMFieldScene::SetGuildChat(char cOn)
{
}

void TMFieldScene::SetKingDomChat(char cOn)
{
}

void TMFieldScene::SendReqBuy(unsigned int dwControlID)
{
}

void TMFieldScene::SetSanc()
{
}

void TMFieldScene::CreateGate(int nZoneIndex, int bInit)
{
}

int TMFieldScene::GetItemFromGround(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::GetWeaponDamage()
{
	return 0;
}

void TMFieldScene::SetMyHumanMagic()
{
}

void TMFieldScene::SetWeather(int nWeather)
{
}

void TMFieldScene::SetVisibleKhepraPortal(bool bVisible)
{
}

void TMFieldScene::InitBoard()
{
}

int TMFieldScene::LoadMsgText(SListBox* pListBox, char* szFileName)
{
	return 0;
}

void TMFieldScene::SetPosPKRun()
{
}

char TMFieldScene::UseHPotion()
{
	return 0;
}

char TMFieldScene::UseMPotion()
{
	return 0;
}

void TMFieldScene::UsePPotion()
{
}

int TMFieldScene::IsFeedPotion(short sMountIndex, short sItemIndex)
{
	return 0;
}

char TMFieldScene::FeedMount()
{
	return 0;
}

void TMFieldScene::SetRunMode()
{
}

void TMFieldScene::UseTicket(int nCellX, int nCellY)
{
}

char TMFieldScene::UseQuickSloat(char key)
{
	return 0;
}

void TMFieldScene::UpdateFireWorkButton(int nIndex)
{
}

void TMFieldScene::ClearFireWork()
{
}

void TMFieldScene::UseFireWork()
{
}

void TMFieldScene::DrawCustomFireWork(int nIndex)
{
}

void TMFieldScene::TotoSelect()
{
}

void TMFieldScene::TotoBuy()
{
}

void TMFieldScene::TotoClose()
{
}

void TMFieldScene::MobStop(D3DXVECTOR3 vec)
{
}

void TMFieldScene::VisibleInputTradeName()
{
}

void TMFieldScene::VisibleInputPass()
{
}

void TMFieldScene::VisibleInputGuildName()
{
}

void TMFieldScene::VisibleInputCharName(SGridControlItem* pItem, int nCellX, int nCellY)
{
}

void TMFieldScene::UseItem(SGridControlItem* pItem, int nType, int nItemSIndex, int nCellX, int nCellY)
{
}

void TMFieldScene::SendCapsuleItem()
{
}

void TMFieldScene::SetQuestStatus(bool bStart)
{
}

void TMFieldScene::UpdateQuestTime()
{
}

void TMFieldScene::SetButtonTextXY(SButton* pButton)
{
}

int TMFieldScene::OnMsgBoxEvent(unsigned int idwControlID, unsigned int idwEvent, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::OnKeyDebug(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeySkill(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyDash(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyPlus(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyPK(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyName(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyAutoTarget(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyAuto(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyHelp(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyRun(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyFeedMount(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyHPotion(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyMPotion(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyPPotion(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeySkillPage(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyQuestLog(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyReverse(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyAutoRun(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyGuildOnOff(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyShortSkill(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleSkill(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyCamView(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleInven(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleCharInfo(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleMinimap(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleParty(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyReturn(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyNumPad(unsigned int iKeyCode)
{
	return 0;
}

int TMFieldScene::OnKeyTotoTab(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyTotoEnter(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnPacketMessageChat(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketMessageChat_Index(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketMessageChat_Param(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketMessageWhisper(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketLongMessagePanel(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketReqSummon(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCancelSummon(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAction(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSoundEffect(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCreateMob(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFCharacterLogout(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFRemoveServer(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFAccountLogin(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFCharacterLogin(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketItemSold(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketUpdateCargoCoin(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketWeather(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCreateItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFDropItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFGetItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketUpdateItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemoveItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAutoTrade(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSwapItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketShopList(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRMBShopList(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketBuy(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSell(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFMobKill(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketREQParty(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAddParty(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemoveParty(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSetHpMode(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketDeposit(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketWithdraw(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketReqChallange(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCloseShop(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSetShortSkill(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketClearMenu(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCombineComplete(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCastleState(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketStartTime(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemainCount(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketWarInfo(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketGuildDisable(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketEnvEffect(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemainNPCCount(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRESULTGAMBLE(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketREQArray(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAttack(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketNuke(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRandomQuiz(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAutoKick(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketItemPrice(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCapsuleInfo(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRunQuest12Start(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRunQuest12Count(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketDelayQuit(MSG_STANDARDPARM* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketUndoSellItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::Guildmark_Create(stGuildMarkInfo* pMark)
{
	return 0;
}

void TMFieldScene::Guildmark_MakeFileName(char* szStr, int nGuild, int nChief, int nChannel)
{
}

int TMFieldScene::Guildmark_Find_ArrayIndex(int nGuild)
{
	return 0;
}

int TMFieldScene::Guildmark_Find_EmptyArrayIndex()
{
	return 0;
}

int TMFieldScene::Guildmark_DeleteIdleGuildmark()
{
	return 0;
}

int TMFieldScene::Guildmark_IsCorrectBMP(char* szMarkBuffer)
{
	return 0;
}

void TMFieldScene::Guildmark_Link(SPanel* pPanel, int nMarkIndex, int nGuildIndex)
{
}

void TMFieldScene::SysMsgChat(char* str)
{
}

void TMFieldScene::GetTimeString(char* szVal, int sTime, int nTime, int i)
{
}

void TMFieldScene::Bag_View()
{
}

void TMFieldScene::AirMove_Main(unsigned int dwServerTime)
{
}

void TMFieldScene::AirMove_Start(int nIndex)
{
}

void TMFieldScene::AirMove_End()
{
}

int TMFieldScene::AirMove_ShowUI(bool bShow)
{
	return 0;
}

int TMFieldScene::Affect_Main(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::StrByteCheck(char* szString)
{
	return 0;
}

void TMFieldScene::SetVisibleMixPanel(int bShow)
{
}

void TMFieldScene::ClearMixPannel()
{
}

void TMFieldScene::SetVisibleMissionPanel(int bShow)
{
}

void TMFieldScene::ClearMissionPannel()
{
}

void TMFieldScene::GameAuto()
{
}

int TMFieldScene::MouseClick_MixNPC(TMHuman* pOver)
{
	return 0;
}

void TMFieldScene::MouseClick_PremiumNPC(TMHuman* pOver)
{
}

int TMFieldScene::MouseClick_SkillMasterNPC(unsigned int dwServerTime, TMHuman* pOver)
{
	return 0;
}

int TMFieldScene::MouseClick_QuestNPC(unsigned int dwServerTime, TMHuman* pOver)
{
	return 0;
}

void TMFieldScene::NewCCMode()
{
}
