//#pragma once
//#include <D3D9Types.h>
//#include <DirectXMath.h>
//#include "stdafx.h"
//class LightClass
//{
//public:
//	LightClass();
//	LightClass(const LightClass&);
//	~LightClass();
//
//	typedef struct D3DLIGH9
//	{
//		D3DLIGHTTYPE Type;
//		D3DCOLORVALUE Diffuse;
//		D3DCOLORVALUE Specular;
//		D3DCOLORVALUE Ambient;
//		D3DVECTOR     Position;
//		D3DVECTOR     Direction;
//		float         Range;
//		float         Falloff;
//		float         Attenuation0;
//		float         Attenuation1;
//		float         Attenuation2;
//		float         Theta;
//		float         Phi;
//
//	}D3DLIGHT9, *LPD3DLIGHT;
//
//	void SetType(D3DLIGHTTYPE type);
//	void SetDiffuseColor(const D3DXCOLOR& color);
//	void SetDirection(const D3DXVECTOR3& direction);
//	void Enable(bool enable);
//
//	void Apply(IDirect3DDevice9* device, DWORD index) const;
//
//private:
//	D3DLIGHT9 m_light;
//	bool m_enabled;
//};
