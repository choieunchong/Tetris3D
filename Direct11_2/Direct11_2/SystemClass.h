#pragma once


class InputClass;
class GraphicsClass;


class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize(); //DirectX를 초기화하고 윈도우를 생성
	void Shutdown(); //DirectX를 해제하고 윈도우를 닫는 함수
	void Run(); // 윈도우메시지 루프를 실행하고 업데이트 및 렌더링을 수앵하는 함수

	//HWND 윈도우의 핸들, UINT 메세지의 ID, WPARAM LPARAM 메시지의 추가 정보
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame(); // 한 프레임마다 호출되는 함수, 입력, 업데이트, 렌더링 등을 수행
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