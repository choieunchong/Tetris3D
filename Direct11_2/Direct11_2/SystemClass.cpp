#include "stdafx.h"
#include "inputclass.h"
#include "graphicsclass.h"
#include "systemclass.h"
#include "CameraClass.h"
#include <iostream>
// SystemClass Window�� �Լ��� ����Ͽ�, ȭ�鱸�� �� ���� �ڵ��� �����ϸ�
// �����Ӹ��� �Է��� �ްų� Ư���� �ൿ�� ���Ѵ�

SystemClass::SystemClass()
{

}


SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize() //�ʱ�ȭ �Լ�
{
	// ������ â ����, ���� ���� ���� �ʱ�ȭ
	int screenWidth = 0;
	int screenHeight = 0;

	// ������ ���� �ʱ�ȭ
	InitializeWindows(screenWidth, screenHeight);

	// m_Input ��ü ����. �� Ŭ������ ���� ������� Ű���� �Է� ó���� ���˴ϴ�.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// m_Input ��ü �ʱ�ȭ
	m_Input->Initialize();

	// m_Graphics ��ü ����.  �׷��� �������� ó���ϱ� ���� ��ü�Դϴ�.
	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}


	// m_Graphics ��ü �ʱ�ȭ.
	return m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
}


void SystemClass::Shutdown()
{
	// m_Graphics ��ü ��ȯ
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// m_Input ��ü ��ȯ
	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	// Window ���� ó��
	ShutdownWindows();
}


void SystemClass::Run()
{
	// �޽��� ����ü ���� �� �ʱ�ȭ
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); // 0���� �ʱ�ȭ ���ش�.
	// 0���� �ʱ�ȭ ���ִ� ���� msg ����ü ��� ����� �ʱ�ȭ �Ͽ� ������ �Ҵ� �Ǿ��� ���� �� ����

	// ����ڷκ��� ���� �޽����� ���������� �޽��������� ���ϴ�
	while (true)
	{
		// ������ �޽����� ó���մϴ�
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ���� �޽����� ���� ��� �޽��� ������ Ż���մϴ�
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg); // WM_CHAR �޽����� ����� �޽��� ť�� �����δ�.
			DispatchMessage(&msg); // �޽����� ������ ���ν����� ������
		}
		else
		{
			// �� �ܿ��� Frame �Լ��� ó���մϴ�.
			if (!Frame())
				break;
		}
	}
}


bool SystemClass::Frame()
{
	
	// ESC Ű ���� �� ���� ���θ� ó���մϴ�
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}
	
	// �׷��� ��ü�� Frame�� ó���մϴ�
	return m_Graphics->Frame();
}

// MessageHandler() �Լ��� ������ �ý��� �޽����� �ٷ� �������� ��
LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Ű���尡 �������°� ó��
	case WM_KEYDOWN:
	{
		// Ű ���� flag�� m_Input ��ü�� ó���ϵ��� �մϴ�
		m_Input->KeyDown((unsigned int)wparam);
		return 0;
	}

	// Ű���尡 �������°� ó��
	case WM_KEYUP:
	{
		// Ű ���� flag�� m_Input ��ü�� ó���ϵ��� �մϴ�.
		m_Input->KeyUp((unsigned int)wparam);
		return 0;
	}

	// �� ���� ��� �޽������� �⺻ �޽��� ó���� �ѱ�ϴ�.
	default:
	{ // wparm �� lparam�� ���콺/Ű���� ��ư�� ���¿� ���콺 Ŀ���� ��ġ�� ����Ǿ� �ִ�.
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}

// ������ �ϴµ� ����� ������(â)�� ����
void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	// �ܺ� �����͸� �� ��ü�� �����մϴ�
	ApplicationHandle = this;

	// �� ���α׷��� �ν��Ͻ��� �����ɴϴ�
	m_hinstance = GetModuleHandle(NULL);

	// ���α׷� �̸��� �����մϴ�
	m_applicationName = L"Dx11";

	// windows Ŭ������ �Ʒ��� ���� �����մϴ�.
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // ���� ũ�⺯�� | ���� ũ�⺯�� | ����������� ���� DC�� �Ҵ�� 
	wc.lpfnWndProc = WndProc; // �޼���ó�� �Լ� ���콺 �����ͷ� �ѱ��.
	wc.cbClsExtra = 0; // Ŭ���� ���� �޸�
	wc.cbWndExtra = 0; // ������ ���� �޸�
	wc.hInstance = m_hinstance; // �ν��Ͻ��� �ѱ��.
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon; // ������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ��
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // ���� �ٲٱ�
	wc.lpszMenuName = NULL; // �޴� �̸�
	wc.lpszClassName = m_applicationName; //Ŭ���� �̸�
	wc.cbSize = sizeof(WNDCLASSEX);

	// windows class�� ����մϴ�
	RegisterClassEx(&wc);

	// ����� ȭ���� �ػ󵵸� �о�ɴϴ�
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int posX = 0;
	int posY = 0;

	// FULL_SCREEN ���� ���� ���� ȭ���� �����մϴ�.
	if (FULL_SCREEN)
	{
		// Ǯ��ũ�� ���� �����ߴٸ� ����� ȭ�� �ػ󵵸� ����ũ�� �ػ󵵷� �����ϰ� ������ 32bit�� �����մϴ�.
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings)); // �޸� �ʱ�ȭ
		dmScreenSettings.dmSize = sizeof(dmScreenSettings); // �ػ� ����
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth; // ���ϴ� �ػ� �ʺ�
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight; // ���ϴ� �ػ� ����
		dmScreenSettings.dmBitsPerPel = 32; // 32bit �ػ󵵷� ���� // �÷� ������ �� �پ��ϰ� �����ϰ� ǥ���ϱ� ���� 32bit ���
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Ǯ��ũ������ ���÷��� ������ �����մϴ�.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		// ������ ����� ��� 800 * 600 ũ�⸦ �����մϴ�.
		screenWidth = 800;
		screenHeight = 600;

		// ������ â�� ����, ������ �� ��� ������ �մϴ�.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// �����츦 �����ϰ� �ڵ��� ���մϴ�.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// �����츦 ȭ�鿡 ǥ���ϰ� ��Ŀ���� �����մϴ�
	// ������ (â)�� ���� ����(���ϼ��� ���̸� �Ʒ��ϼ��� �ٸ� ȭ��鿡 ��������).
	// (���� �۾����� �������) Ȱ��ȭ
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);// ��Ŀ���� �༭ �ֻ����� ������ �����.
	SetFocus(m_hwnd);
}


void SystemClass::ShutdownWindows()
{
	// Ǯ��ũ�� ��忴�ٸ� ���÷��� ������ �ʱ�ȭ�մϴ�.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// â�� �����մϴ�
	DestroyWindow(m_hwnd); // view�� ������ �� ȣ��Ǵ� �ڵ鷯
	m_hwnd = NULL;

	// ���α׷� �ν��Ͻ��� �����մϴ�
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// �ܺ������� ������ �ʱ�ȭ�մϴ�
	ApplicationHandle = NULL;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// ������ ���Ḧ Ȯ���մϴ�
	case WM_DESTROY:// �޽��� ó���� ������ �ܰ�
	{
		PostQuitMessage(0);
		return 0;
	}

	// �����찡 �������� Ȯ���մϴ�
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� ��� �޽������� �ý��� Ŭ������ �޽��� ó���� �ѱ�ϴ�.
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}