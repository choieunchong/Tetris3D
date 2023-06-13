#pragma once


class InputClass;
class GraphicsClass;


class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize(); //DirectX�� �ʱ�ȭ�ϰ� �����츦 ����
	void Shutdown(); //DirectX�� �����ϰ� �����츦 �ݴ� �Լ�
	void Run(); // ������޽��� ������ �����ϰ� ������Ʈ �� �������� �����ϴ� �Լ�

	//HWND �������� �ڵ�, UINT �޼����� ID, WPARAM LPARAM �޽����� �߰� ����
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame(); // �� �����Ӹ��� ȣ��Ǵ� �Լ�, �Է�, ������Ʈ, ������ ���� ����
	void InitializeWindows(int&, int&); 
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input = nullptr;
	GraphicsClass* m_Graphics = nullptr;

};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* ApplicationHandle = 0;