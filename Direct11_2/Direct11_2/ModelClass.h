#pragma once
// 위치벡터(x,y,z)
// 텍스쳐 좌표(tu, tv)
// 법선 벡터(nx, ny, nz)


class ModelClass : public AlignedAllocationPolicy<16>
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};


public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	

	//Box 만들기
	//HRESULT D3DXCreateBox(__in LPDIRECT3DDEVICE9 pDevice, __in FLOAT Width, __in FLOAT Height, __in FLOAT Depth,
	//	__out LPD3DXMESH *ppMesh, __out LPD3DXBUFFER);
	//HRESULT CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, 
	//							LPDIRECT3DINDEXBUFFER9 ppIndexBuffer,HANDLE* pSharedHandle);

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
};