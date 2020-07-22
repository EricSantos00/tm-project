#include "pch.h"
#include "EventTranslator.h"

EventTranslator::EventTranslator()
{
}

EventTranslator::~EventTranslator()
{
}

BOOL EventTranslator::Initialize(HWND hWnd)
{
	return 1;
}

int EventTranslator::InitializeIME()
{
	return 1;
}

int EventTranslator::InitializeInputDevice(HWND hWnd)
{
	return 1;
}

void EventTranslator::Finalize()
{
}

void EventTranslator::FinalizeIME()
{
}

BOOL EventTranslator::IsNative()
{
	return 0;
}

void EventTranslator::SetIMENative()
{
}

void EventTranslator::SetIMEAlphaNumeric()
{
}

void EventTranslator::SetIMEOpenStatus(int bOpen)
{
}

int EventTranslator::IsIMEOpenStatus()
{
	return 0;
}

void EventTranslator::SetVisibleCandidateList(int lParam, int bVisible)
{
}

void EventTranslator::Lock()
{
}

void EventTranslator::Unlock()
{
}

int EventTranslator::ReadInputEventData()
{
	return 0;
}

int EventTranslator::CameraEventData()
{
	return 0;
}

void EventTranslator::OnKeyDown(unsigned int iKeyCode)
{
}

void EventTranslator::OnKeyUp(unsigned int iKeyCode)
{
}

void EventTranslator::OnChar(char iCharCode, int lParam)
{
}

void EventTranslator::OnIME(char iCharCode, int lParam)
{
}

void EventTranslator::OnIME2()
{
}

void EventTranslator::UpdateCompositionPos()
{
}

void EventTranslator::OnLMousePressed()
{
}

void EventTranslator::OnLMouseReleased()
{
}

void EventTranslator::OnRMousePressed()
{
}

void EventTranslator::OnRMouseReleased()
{
}

void EventTranslator::OnMouseEvent(unsigned int nFlags, unsigned int wParam, int ix, int iy)
{
}
