#include "pch.h"
#include "SelectGDI.h"

#include "CGameProcess.h"



SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
}
