#include "stdafx.h"
#include "modelclass.h"

// 3D 모델을 로드하고 각 모델의 정점 데이터, 텍스처 데이터, 인덱스 버퍼 등을 저장
// 모델을 렌더링하고, 텍스처매핑, 조명, 그림자 등의 효과를 적용하여 시각적인 효과를 
// 생성할 수 있다.
// V는 정점을 의미한다 육면제는 꼭지점 8개이므로 8개의 정점을 가진다
// VT 텍스쳐 좌표를 의미한다 모든 삼각형의 모든 정점에 대한 기록을 하기 때문에 중복되는 내용이 많다 각 좌표는 TU, TV로 float형 포맷이다.
// VN은 법선 벡터이다 육면체는 24개의 법선 벡터가 있고 모든  삼각형의 모든 정점에 대한 기록을 하기 때문에 중복되는 내용이 많다.(NX, NY, NZ의 float형 포맷)
// F줄은 육면체 모델의 삼각형 (표면)을 의미 나열된 값들은 정점의 순서(인덱스), 텍스쳐 좌표들, 법선 벡터들 이다.
// f 정점 1/ 텍스처 1/ 법선1 정점2/텍스쳐2/법선2 정점3/텍스쳐3/법선3
ModelClass::ModelClass()
{

}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device)
{
	// 정점 및 인덱스 버퍼를 초기화합니다.
	return InitializeBuffers(device);
}


void ModelClass::Shutdown()
{
	// 버텍스 및 인덱스 버퍼를 종료합니다.
	ShutdownBuffers();
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// 그리기를 준비하기 위해 그래픽 파이프 라인에 꼭지점과 인덱스 버퍼를 놓습니다.
	RenderBuffers(deviceContext);
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}



bool ModelClass::InitializeBuffers(ID3D11Device* device)
{	
	// 정점 배열의 정점 수를 설정합니다.
	//m_vertexCount = 3;
	m_vertexCount = 8;

	// 인덱스 배열의 인덱스 수를 설정합니다.
	//m_indexCount = 3;
	m_indexCount = 36;

	// 정점 배열을 만듭니다.
	VertexType* vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// 인덱스 배열을 만듭니다.
	unsigned long* indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// 정점 배열에 데이터를 설정합니다.
	// 삼각형
/*	vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].color = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);*/

	
	// 사각형 점 위치
	vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);  // Front bottom left
	vertices[1].position = XMFLOAT3(1.0f, -1.0f, 1.0f);   // Front bottom right
	vertices[2].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);   // Front top left
	vertices[3].position = XMFLOAT3(1.0f, 1.0f, 1.0f);    // Front top right
	vertices[4].position = XMFLOAT3(-1.0f, -1.0f, -1.0f); // Back bottom left
	vertices[5].position = XMFLOAT3(1.0f, -1.0f, -1.0f);  // Back bottom right
	vertices[6].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);  // Back top left
	vertices[7].position = XMFLOAT3(1.0f, 1.0f, -1.0f);   // Back top right


	vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	vertices[1].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	vertices[2].color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	vertices[3].color = XMFLOAT4(0.0f, 1.0f, 0.5f, 0.5f);
	vertices[4].color = XMFLOAT4(0.0f, 0.5f, 0.0f, 0.0f);
	vertices[5].color = XMFLOAT4(0.0f, 0.0f, 0.5f, 0.0f);
	vertices[6].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.5f);
	vertices[7].color = XMFLOAT4(0.0f, 1.0f, 0.4f, 0.7f);
	//// Define the colors of the vertices
	//for (int i = 0; i < 8; i++) {
	//	vertices[i].color = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f); 
	//}

	// 그리기 위한 순서
	indices[0] = 0; indices[1] = 1; indices[2] = 2;    // Front face
	indices[3] = 2; indices[4] = 1; indices[5] = 3;
	indices[6] = 1; indices[7] = 5; indices[8] = 3;    // Right face
	indices[9] = 3; indices[10] = 5; indices[11] = 7;
	indices[12] = 5; indices[13] = 4; indices[14] = 7; // Back face
	indices[15] = 7; indices[16] = 4; indices[17] = 6;
	indices[18] = 4; indices[19] = 0; indices[20] = 6; // Left face
	indices[21] = 6; indices[22] = 0; indices[23] = 2;
	indices[24] = 2; indices[25] = 3; indices[26] = 6; // Top face
	indices[27] = 6; indices[28] = 3; indices[29] = 7;
	indices[30] = 0; indices[31] = 4; indices[32] = 1; // Bottom face
	indices[33] = 1; indices[34] = 4; indices[35] = 5;



	// 정적 정점 버퍼의 구조체를 설정합니다.
	D3D11_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 버텍스버퍼로써 바인드
    vertexBufferDesc.CPUAccessFlags = 0;// CPU액세스 하지 않음
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;


	// subresource 구조에 정점 데이터에 대한 포인터를 제공합니다.
	D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = vertices;// 버퍼 데이터 초기화
	vertexData.SysMemPitch = 0;// 메모리의 Pitch값
	vertexData.SysMemSlicePitch = 0;// 깊이 레벨(3D텍스처 리소스에서만 사용)

	// 이제 정점 버퍼를 만듭니다.
	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
	{
		return false;
	}

	// 정적 인덱스 버퍼의 구조체를 설정합니다.
	
	D3D11_BUFFER_DESC indexBufferDesc;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0; // 사용하지 않는다
	indexBufferDesc.StructureByteStride = 0;

	// 인덱스 데이터를 가리키는 보조 리소스 구조체를 작성합니다.
	// 인덱스 버퍼에 대한 정보를 저장하기 위해 사용된다
	// 인덱스 크기와 형식, 인덱스 데이터를 저장하는 메모리의 위치를 지정합니다.
	D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = indices; // 메모리의 시작주소
	indexData.SysMemPitch = 0; // 행 간격
	indexData.SysMemSlicePitch = 0; // 면 간격

	// 인덱스 버퍼를 생성합니다.
	if(FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer)))
	{
		return false;
	}

	// 생성되고 값이 할당된 정점 버퍼와 인덱스 버퍼를 해제합니다.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// 인덱스 버퍼를 해제합니다.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// 정점 버퍼를 해제합니다.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	// 정점 버퍼의 단위와 오프셋을 설정합니다.
	// 각 정점의 데이터가 어디부터 시작하는지 알기 위해
	unsigned int stride = sizeof(VertexType); 
	unsigned int offset = 0;
    
	// 렌더링 할 수 있도록 입력 어셈블러에서 정점 버퍼를 활성으로 설정합니다.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // 렌더링 할 수 있도록 입력 어셈블러에서 인덱스 버퍼를 활성으로 설정합니다.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // 정점 버퍼로 그릴 기본형을 설정합니다. 여기서는 삼각형으로 설정합니다.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}