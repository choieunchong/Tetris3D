#pragma once
#include "macro.h"

// 2023-05-22 ecchoi [ Ű �Է��� �ޱ� ���� Ŭ���� ]

class InputClass
{
public:
	InputClass();
	~InputClass();

	void Initialize();
	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	// Left Ű �Է½� �������� �̵�
	void KeyLeft(unsigned int);
	// Right Ű �Է½� �������� �̵�
	void KeyRight(unsigned int);
	// keyZ Ű �Է½� ȸ��
	void keyZ(unsigned int);
	void keyX(unsigned int);
	bool IsKeyDown(unsigned int);


private:
	bool m_bKey[256];
};

