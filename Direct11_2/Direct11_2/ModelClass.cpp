#include "stdafx.h"
#include "modelclass.h"

// 3D ���� �ε��ϰ� �� ���� ���� ������, �ؽ�ó ������, �ε��� ���� ���� ����
// ���� �������ϰ�, �ؽ�ó����, ����, �׸��� ���� ȿ���� �����Ͽ� �ð����� ȿ���� 
// ������ �� �ִ�.
// V�� ������ �ǹ��Ѵ� �������� ������ 8���̹Ƿ� 8���� ������ ������
// VT �ؽ��� ��ǥ�� �ǹ��Ѵ� ��� �ﰢ���� ��� ������ ���� ����� �ϱ� ������ �ߺ��Ǵ� ������ ���� �� ��ǥ�� TU, TV�� float�� �����̴�.
// VN�� ���� �����̴� ����ü�� 24���� ���� ���Ͱ� �ְ� ���  �ﰢ���� ��� ������ ���� ����� �ϱ� ������ �ߺ��Ǵ� ������ ����.(NX, NY, NZ�� float�� ����)
// F���� ����ü ���� �ﰢ�� (ǥ��)�� �ǹ� ������ ������ ������ ����(�ε���), �ؽ��� ��ǥ��, ���� ���͵� �̴�.
// f ���� 1/ �ؽ�ó 1/ ����1 ����2/�ؽ���2/����2 ����3/�ؽ���3/����3
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
	// ���� �� �ε��� ���۸� �ʱ�ȭ�մϴ�.
	return InitializeBuffers(device);
}


void ModelClass::Shutdown()
{
	// ���ؽ� �� �ε��� ���۸� �����մϴ�.
	ShutdownBuffers();
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// �׸��⸦ �غ��ϱ� ���� �׷��� ������ ���ο� �������� �ε��� ���۸� �����ϴ�.
	RenderBuffers(deviceContext);
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}



bool ModelClass::InitializeBuffers(ID3D11Device* device)
{	
	// ���� �迭�� ���� ���� �����մϴ�.
	//m_vertexCount = 3;
	m_vertexCount = 8;

	// �ε��� �迭�� �ε��� ���� �����մϴ�.
	//m_indexCount = 3;
	m_indexCount = 36;

	// ���� �迭�� ����ϴ�.
	VertexType* vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// �ε��� �迭�� ����ϴ�.
	unsigned long* indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// ���� �迭�� �����͸� �����մϴ�.
	// �ﰢ��
/*	vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].color = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);*/

	
	// �簢�� �� ��ġ
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

	// �׸��� ���� ����
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



	// ���� ���� ������ ����ü�� �����մϴ�.
	D3D11_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ���ؽ����۷ν� ���ε�
    vertexBufferDesc.CPUAccessFlags = 0;// CPU�׼��� ���� ����
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;


	// subresource ������ ���� �����Ϳ� ���� �����͸� �����մϴ�.
	D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = vertices;// ���� ������ �ʱ�ȭ
	vertexData.SysMemPitch = 0;// �޸��� Pitch��
	vertexData.SysMemSlicePitch = 0;// ���� ����(3D�ؽ�ó ���ҽ������� ���)

	// ���� ���� ���۸� ����ϴ�.
	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
	{
		return false;
	}

	// ���� �ε��� ������ ����ü�� �����մϴ�.
	
	D3D11_BUFFER_DESC indexBufferDesc;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0; // ������� �ʴ´�
	indexBufferDesc.StructureByteStride = 0;

	// �ε��� �����͸� ����Ű�� ���� ���ҽ� ����ü�� �ۼ��մϴ�.
	// �ε��� ���ۿ� ���� ������ �����ϱ� ���� ���ȴ�
	// �ε��� ũ��� ����, �ε��� �����͸� �����ϴ� �޸��� ��ġ�� �����մϴ�.
	D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = indices; // �޸��� �����ּ�
	indexData.SysMemPitch = 0; // �� ����
	indexData.SysMemSlicePitch = 0; // �� ����

	// �ε��� ���۸� �����մϴ�.
	if(FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer)))
	{
		return false;
	}

	// �����ǰ� ���� �Ҵ�� ���� ���ۿ� �ε��� ���۸� �����մϴ�.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// �ε��� ���۸� �����մϴ�.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// ���� ���۸� �����մϴ�.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	// ���� ������ ������ �������� �����մϴ�.
	// �� ������ �����Ͱ� ������ �����ϴ��� �˱� ����
	unsigned int stride = sizeof(VertexType); 
	unsigned int offset = 0;
    
	// ������ �� �� �ֵ��� �Է� ��������� ���� ���۸� Ȱ������ �����մϴ�.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // ������ �� �� �ֵ��� �Է� ��������� �ε��� ���۸� Ȱ������ �����մϴ�.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // ���� ���۷� �׸� �⺻���� �����մϴ�. ���⼭�� �ﰢ������ �����մϴ�.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}