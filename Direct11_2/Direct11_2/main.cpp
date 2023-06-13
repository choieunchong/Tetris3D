// SydtemClass�� ����� SystemClass�� ���۵ǵ��� �����

#include "stdafx.h"
#include "SystemClass.h"

#ifdef _DEBUG

#pragma comment(linker, "/entry.winMainCRTStartup /subsystem.console")
#endif

//#pragma comment(linker, "/entry:winMainCRTStartup /subsystem:console")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // ���� ���α׷��� �ν��Ͻ� �ڵ�
	_In_opt_ HINSTANCE hPrevInstance, // ���� �ν��Ͻ� �ڵ�
	_In_ LPWSTR lpCmdLine, // �����ڵ� ���ڿ��� �޾Ƶ��̱� ����
	_In_ int nCmdShow) // ������ �ʱ� ǥ�� ����
{
	AllocConsole();
	HWND consoleHandle = GetConsoleWindow();

	//RECT consoleRect;
	//GetWindowRect(consoleHandle, &consoleRect);
	//moveWindow(consoleHandle, consoleRect.left, consoleRect.top,800,600,true);

	// System ��ü ����
	SystemClass* System = new SystemClass;
	if (!System)
	{
		return -1;
	}

	// System ��ü �ʱ�ȭ �� ����
	if (System->Initialize())
	{
		System->Run();
	}

	// System ��ü ���� �� �޸� ��ȯ
	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;
}