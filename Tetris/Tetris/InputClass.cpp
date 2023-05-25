#include "InputClass.h"

InputClass::InputClass()
{
	cout << "InputClass";
	m_bKey[256] = { 0, };
}

InputClass::~InputClass()
{
}

void InputClass::Initialize()
{
	// 키 배열을 초기화
	for (int i = 0; i < 256; i++)
	{
		m_bKey[i] = false;
	}
}

void InputClass::KeyDown(unsigned int input)
{

	m_bKey[input] = true;
}

void InputClass::KeyUp(unsigned int input)
{
	m_bKey[input] = false;
}

void InputClass::KeyLeft(unsigned int input)
{
	m_bKey[input] = true;
}

void InputClass::KeyRight(unsigned int input)
{
	m_bKey[input] = true;
}

void InputClass::keyZ(unsigned int input)
{
	m_bKey[input];
}

void InputClass::keyX(unsigned int input)
{
	m_bKey[input];
}

bool InputClass::IsKeyDown(unsigned int key)
{
	// 현재 키 값이 눌러 졌는지 상태를 반환
	return m_bKey[key] ; 
}


