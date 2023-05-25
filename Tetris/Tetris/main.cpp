#include "DrawTetris.h"

int main()
{
	DrawTetris* m_pDrawTetris = new DrawTetris;

	if (!m_pDrawTetris)
	{
		return -1;
	}

	if (!m_pDrawTetris->bInitialize())
	{
		m_pDrawTetris->Run();
	}

	m_pDrawTetris->DrawBlockMap();
	delete m_pDrawTetris;
	m_pDrawTetris = nullptr;

	return 0;
}