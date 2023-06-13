// SydtemClass를 만들어 SystemClass가 시작되도록 만든다

#include "stdafx.h"
#include "SystemClass.h"

#ifdef _DEBUG

#pragma comment(linker, "/entry.winMainCRTStartup /subsystem.console")
#endif

//#pragma comment(linker, "/entry:winMainCRTStartup /subsystem:console")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 응용 프로그램의 인스턴스 핸들
	_In_opt_ HINSTANCE hPrevInstance, // 이전 인스턴스 핸들
	_In_ LPWSTR lpCmdLine, // 유니코드 문자열을 받아들이기 위해
	_In_ int nCmdShow) // 윈도우 초기 표시 상태
{
	AllocConsole();
	HWND consoleHandle = GetConsoleWindow();

	//RECT consoleRect;
	//GetWindowRect(consoleHandle, &consoleRect);
	//moveWindow(consoleHandle, consoleRect.left, consoleRect.top,800,600,true);

	// System 객체 생성
	SystemClass* System = new SystemClass;
	if (!System)
	{
		return -1;
	}

	// System 객체 초기화 및 실행
	if (System->Initialize())
	{
		System->Run();
	}

	// System 객체 종료 및 메모리 반환
	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;
}