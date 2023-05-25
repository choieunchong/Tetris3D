#pragma once
#include "macro.h"

// 2023-05-22 ecchoi [ 키 입력을 받기 위한 클래스 ]

class InputClass
{
public:
	InputClass();
	~InputClass();

	void Initialize();
	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	// Left 키 입력시 좌측으로 이동
	void KeyLeft(unsigned int);
	// Right 키 입력시 우측으로 이동
	void KeyRight(unsigned int);
	// keyZ 키 입력시 회전
	void keyZ(unsigned int);
	void keyX(unsigned int);
	bool IsKeyDown(unsigned int);


private:
	bool m_bKey[256];
};

