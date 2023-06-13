#include "stdafx.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
#include "graphicsclass.h"
#include <iostream>

//셰이더, 텍스처, 뷰포트 및 렌더 타겟 등의 그래픽 리소스를 설정하고 사용하여 렌더링

GraphicsClass::GraphicsClass()
{
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	// Direct3D 객체 생성
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Direct3D 객체 초기화
	if(!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// m_Camera 객체 생성
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// 카메라 포지션 설정
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	// m_Model 객체 생성
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// m_Model 객체 초기화
	if (!m_Model->Initialize(m_Direct3D->GetDevice()))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	// m_ColorShader 객체 생성
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// m_ColorShader 객체 초기화
	if (!m_ColorShader->Initialize(m_Direct3D->GetDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	//FILE* fp = nullptr;
	//fopen_s(&fp, "비디오 카드 정보.txt", "wt");
	//if (fp != nullptr) 
	//{
	//	char cardName[256];
	//	int memory = 0;
	//	m_Direct3D->GetVideoCardInfo(cardName, memory);
	//	fprintf_s(fp, " 그래픽카드 이름:%s\n", cardName);
	//	fprintf_s(fp, " 그래픽카드 메모리 크기:%s\n", memory);
	//	fclose(fp);
	//}


	return true;
}


void GraphicsClass::Shutdown()
{
	// m_ColorShader 객체 반환
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// m_Model 객체 반환
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// m_Camera 객체 반환
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Direct3D 객체 반환
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
}


bool GraphicsClass::Frame()
{
	static float rotation = 0.0f;
	// 각 프레임의 rotation 변수를 업데이트 합니다
	rotation += (float)XM_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation == 360.0f;
	}
	// 그래픽 랜더링 처리
	return Render(rotation);
}


bool GraphicsClass::Render(float rotation)
{
	// 씬을 그리기 위해 버퍼를 지웁니다
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// 카메라의 위치에 따라 뷰 행렬을 생성합니다
	m_Camera->Render();
	m_Camera->GetPosition();

	// 카메라 및 d3d 객체에서 월드, 뷰 및 투영 행렬을 가져옵니다
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	//삼각형이 회전 할 수 있도록 회전 값으로 월드 행렬을 회전합니다.
	worldMatrix = XMMatrixRotationY(rotation);

	// 모델 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 드로잉을 준비합니다.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	// 색상 쉐이더를 사용하여 모델을 렌더링합니다.
	if (!m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix))
	{
		return false;
	}

	// 버퍼의 내용을 화면에 출력합니다
	m_Direct3D->EndScene();

	return true;
}